#include <iostream>
#include <iomanip>
#include <cassert>
#include <limits>

using uint = unsigned int;
using namespace std;

enum ePoolFunction {is_maximum = 0, is_average = 1, is_minimum = 2};

extern "C" int get_id();
extern "C" {
  #include "acPthread.h"
}

const int MASK_X = 3;
const int MASK_Y = 3;
const int bias = 128;
// global variables in shared memory
volatile mutex_t *mutex = (volatile mutex_t *)0x52ff0000; // 4-byte: 0x52ff0000 - 0x52ff0003
volatile barrier_t *barr = (volatile barrier_t *)0x52ff0004; // 16-byte: 0x52ff0004 - 0x52ff0013

volatile unsigned int* width_global = (volatile unsigned int*) 0x52ff0014;  // 4-byte 0x52ff0014 - 0x52ff0017
volatile unsigned int* height_global = (volatile unsigned int*) 0x52ff0018; // 4-byte 0x52ff0018 - 0x52ff002a
volatile unsigned int* byte_per_pixel_global = (volatile unsigned int*) 0x52ff0030; // 4-byte 0x52ff0018 - 0x52ff002a

volatile unsigned char* image_s =  (volatile unsigned char*) 0x53000000; // source image array
volatile unsigned char* image_t =  (volatile unsigned char*) 0x63000000; // target image array

// private variables
unsigned int width = 0;               // image width
unsigned int height = 0;              // image height
unsigned int rgb_raw_data_offset = 0; // RGB raw data offset
unsigned char bit_per_pixel = 0;      // bit per pixel
unsigned short byte_per_pixel = 0;    // byte per pixel

// bitmap header
unsigned char header[54] = {
    0x42,        // identity : B
    0x4d,        // identity : M
    0, 0, 0, 0,  // file size
    0, 0,        // reserved1
    0, 0,        // reserved2
    54, 0, 0, 0, // RGB data offset
    40, 0, 0, 0, // struct BITMAPINFOHEADER size
    0, 0, 0, 0,  // bmp width
    0, 0, 0, 0,  // bmp height
    1, 0,        // planes
    24, 0,       // bit per pixel
    0, 0, 0, 0,  // compression
    0, 0, 0, 0,  // data size
    0, 0, 0, 0,  // h resolution
    0, 0, 0, 0,  // v resolution
    0, 0, 0, 0,  // used colors
    0, 0, 0, 0   // important colors
};

const double embossfiltermask[3][3] =
{
        -1, -1, 0,
        -1, 0, 1,
        0, 1, 1
};

int read_bmp(const char *fname_s);
int emboss(const int y_start);
int write_bmp(const char *fname_t);

FILE *fp_s = nullptr;             // source file handler
FILE *fp_t = nullptr;             // target file handler



int main(int argc, char *argv[]) {
        /////////////////////////////
        // thread and barrier init //
        /////////////////////////////
        int PROCESSORS = 4;
        barrier_init(barr,PROCESSORS);

        cout << "###########################\n"
             << "# Entering RISC-V process " << get_id() << "\n"
             << "###########################\n" << endl;

		if (get_id() == 1) {
			read_bmp("../lena.bmp");
			*width_global = width;
			*height_global = height;
			*byte_per_pixel_global = byte_per_pixel;
		}
		mutex_init(mutex, NULL);
        
        barrier(barr);
        //		y_offset to start emboss
        emboss(*height_global / 4 * get_id());

        barrier(barr);
    		
        if (get_id() == 1)
	 		assert(write_bmp("lena_emboss.bmp") == 0);

        cout << "\n##########################\n"
             << "# Leaving RISC-V process " << get_id() << "\n"
             << "##########################" << endl;

        barrier(barr);

	return 0;
}

int read_bmp(const char *fname_s)
{
  fp_s = fopen(fname_s, "rb");
  if (fp_s == nullptr)
  {
    std::cerr << "fopen fp_s error" << std::endl;
    return -1;
  }

  // move offset to 10 to find rgb raw data offset
  fseek(fp_s, 10, SEEK_SET);
  assert(fread(&rgb_raw_data_offset, sizeof(unsigned int), 1, fp_s));

  // move offset to 18 to get width & height;
  fseek(fp_s, 18, SEEK_SET);
  assert(fread(&width, sizeof(unsigned int), 1, fp_s));
  assert(fread(&height, sizeof(unsigned int), 1, fp_s));

  // get bit per pixel
  fseek(fp_s, 28, SEEK_SET);
  assert(fread(&bit_per_pixel, sizeof(unsigned short), 1, fp_s));
  byte_per_pixel = bit_per_pixel / 8;

  // move offset to rgb_raw_data_offset to get RGB raw data
  fseek(fp_s, rgb_raw_data_offset, SEEK_SET);

  size_t size = width * height * byte_per_pixel;

  assert(fread((void *)image_s, sizeof(unsigned char),
               (size_t)(long)width * height * byte_per_pixel, fp_s));
  fclose(fp_s);

  return 0;
}

int emboss(const int y_start)
{
  unsigned int x, y, i, v, u;              // for loop counter
  v = 0;
  u = 0;
  int R, G, B, newR, newG, newB; // color of R, G, B
  int adjustX, adjustY, xBound, yBound;
  for (y = y_start; y != y_start + *height_global / 4; ++y)
  {
    for (x = 0; x != *width_global; ++x)
    {
		adjustX = (MASK_X % 2) ? 1 : 0;
		adjustY = (MASK_Y % 2) ? 1 : 0;
		xBound = MASK_X / 2;
		yBound = MASK_Y / 2;
		newR = newG = newB = 0;
      // run filter here

      for (v = -yBound; v != yBound + adjustY; ++v)
      {
        for (u = -xBound; u != xBound + adjustX; ++u)
        {
          if (x + u >= 0 && x + u < *width_global && y + v >= 0 && y + v < *height_global)
          {
            R = *(image_s + (*byte_per_pixel_global) * (*width_global * (y + v) + (x + u)) + 2);
            G = *(image_s + (*byte_per_pixel_global) * (*width_global * (y + v) + (x + u)) + 1);
            B = *(image_s + (*byte_per_pixel_global) * (*width_global * (y + v) + (x + u)) + 0);
           	// printf("get_id() = %d R =%dG =%d B=%d\n", get_id(), R, G, B);
            newR += R * embossfiltermask[u + xBound][v + yBound];
            newG += G * embossfiltermask[u + xBound][v + yBound];
            newB += B * embossfiltermask[u + xBound][v + yBound];
          }
        }
      }
		*(image_t + *byte_per_pixel_global * (*width_global * y + x) + 2) = 
		int(min(max(newR + bias, 0), 255));
		*(image_t + *byte_per_pixel_global * (*width_global * y + x) + 1) = 
		int(min(max(newG + bias, 0), 255));
		*(image_t + *byte_per_pixel_global * (*width_global * y + x) + 0) = 
		int(min(max(newB + bias, 0), 255));
    
    }
  }

  return 0;
}


int write_bmp(const char *fname_t)
{
  unsigned int file_size = 0; // file size

  fp_t = fopen(fname_t, "wb");
  if (fp_t == nullptr)
  {
    std::cerr << "fopen fname_t error" << std::endl;
    return -1;
  }

  // file size
  file_size = width * height * byte_per_pixel + rgb_raw_data_offset;
  header[2] = (unsigned char)(file_size & 0x000000ff);
  header[3] = (file_size >> 8) & 0x000000ff;
  header[4] = (file_size >> 16) & 0x000000ff;
  header[5] = (file_size >> 24) & 0x000000ff;

  // width
  header[18] = width & 0x000000ff;
  header[19] = (width >> 8) & 0x000000ff;
  header[20] = (width >> 16) & 0x000000ff;
  header[21] = (width >> 24) & 0x000000ff;

  // height
  header[22] = height & 0x000000ff;
  header[23] = (height >> 8) & 0x000000ff;
  header[24] = (height >> 16) & 0x000000ff;
  header[25] = (height >> 24) & 0x000000ff;

  // bit per pixel
  header[28] = bit_per_pixel;

  // write header
  fwrite(header, sizeof(unsigned char), rgb_raw_data_offset, fp_t);

  // write image
  fwrite((void *)image_t, sizeof(unsigned char),
         (size_t)(long)width * height * byte_per_pixel, fp_t);

  fclose(fp_t);

  return 0;
}