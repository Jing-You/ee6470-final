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

// global variables in shared memory
volatile mutex_t *mutex = (volatile mutex_t *)0x52ff0000; // 4-byte: 0x52ff0000 - 0x52ff0003
volatile barrier_t *barr = (volatile barrier_t *)0x52ff0004; // 16-byte: 0x52ff0004 - 0x52ff0013

void GenTestData(int* data, const int data_num);
void PrintData(int* data, const int channel, const int height, const int width);
void control_hw_pool();



typedef struct {
	ePoolFunction pool_function;
	int* data_in_ptr;
	int* data_out_ptr;
	uint data_cube_in_width;
	uint data_cube_in_height;
	uint data_cube_in_channel;
	uint data_cube_out_width;
	uint data_cube_out_height;
	uint data_cube_out_channel;
	uint filter_width;
	uint filter_stride;
	uint zero_padding;
} PoolConfig;

void GenTestData(int* const data, const uint data_num);
void PrintData(const int* const data, const uint channel, const uint height, const uint width);
void DoPooling(const PoolConfig &pool_config);

int main(int argc, char *argv[]) {
        /////////////////////////////
        // thread and barrier init //
        /////////////////////////////
        int PROCESSORS = 4;
        barrier_init(barr,PROCESSORS);

        cout << "###########################\n"
             << "# Entering RISC-V process " << get_id() << "\n"
             << "###########################\n" << endl;

        if (get_id() == 0) {
		PoolConfig pool_config;
		pool_config.pool_function         = is_maximum;
		pool_config.data_cube_in_width    = 5;
		pool_config.data_cube_in_height   = pool_config.data_cube_in_width;
		pool_config.data_cube_in_channel  = 2;
		pool_config.filter_width          = 3;
		pool_config.filter_stride         = 1;
		pool_config.zero_padding          = 0;
		pool_config.data_cube_out_width  = ((pool_config.data_cube_in_height + 2 * pool_config.zero_padding)
		                                   - pool_config.filter_width) / pool_config.filter_stride + 1;
		pool_config.data_cube_out_height  = pool_config.data_cube_out_width;
		pool_config.data_cube_out_channel = pool_config.data_cube_in_channel;
        
		cout << "[Test information]\n"
		     << "        Pooling function: ";
		switch(pool_config.pool_function) {
			case is_maximum: cout << "maximum"; break;
			case is_average: cout << "average"; break;
			case is_minimum: cout << "minimum"; break;
			default: assert(0 && "This pooling function hasn't been supported yet.");
		}
		cout << '\n'
		     << "               Data type: inting point 32\n"
		     << "    Input data dimension: " << pool_config.data_cube_in_channel
		                                     << " x " << pool_config.data_cube_in_height 
		                                     << " x " << pool_config.data_cube_in_width << '\n'
		     << "            Zero Padding: " << pool_config.zero_padding << '\n'
		     << "     Pooling window size: " << pool_config.filter_width
		                                     << " x " << pool_config.filter_width << '\n'
		     << "   Pooling window stride: " << pool_config.filter_stride << '\n'
		     << "   Output data dimension: " << pool_config.data_cube_out_channel
		                                     << " x " << pool_config.data_cube_out_height
		                                     << " x " << pool_config.data_cube_out_width << '\n' << endl;
        
		uint test_data_num(pool_config.data_cube_in_channel
		                   * pool_config.data_cube_in_height
		                   * pool_config.data_cube_in_width);
		int* test_data = new int[test_data_num];
        
		uint result_num(pool_config.data_cube_out_channel
		                * pool_config.data_cube_out_height
		                * pool_config.data_cube_out_width);
		int* result = new int[result_num];
        
		pool_config.data_in_ptr  = test_data;
		pool_config.data_out_ptr = result;
        
		/* Generate random test data */
		GenTestData(test_data, test_data_num);
        
		cout << "Test data cube:" << endl;
		PrintData(test_data,
		          pool_config.data_cube_in_channel,
		          pool_config.data_cube_in_height,
		          pool_config.data_cube_in_width);
        
		/* Do pooling function */
		DoPooling(pool_config);
        
		/* Print results */
		cout << "Result cube:" << endl;
		PrintData(result,
		          pool_config.data_cube_out_channel,
		          pool_config.data_cube_out_height,
		          pool_config.data_cube_out_width);
		
		if(test_data) delete[] test_data;
		if(result) delete[] result;
	}

        barrier(barr);

        cout << "\n##########################\n"
             << "# Leaving RISC-V process " << get_id() << "\n"
             << "##########################" << endl;

        barrier(barr);

	return 0;
}

void GenTestData(int* const data, const uint data_num) {
	for(uint i = 0; i < data_num; i++)
		data[i] = rand() % 256;
}

void PrintData(const int* const data, const uint channel, const uint height, const uint width) {
	for(uint i = 0; i < channel; i++) {
		cout << "Channel #" << i << '\n';
		for(uint j = 0; j < height; j++) {
			for(uint k = 0; k < width; k++) {
				uint index(i * height * width + j * width + k);
				cout << std::fixed << std::setw(8) << std::setprecision(2) << data[index];
			}
			cout << '\n';
		}
		cout << '\n';
	}
	cout << endl;
}

void DoPooling(const PoolConfig &pool_config) {
	for(uint out_ch_idx = 0; out_ch_idx < pool_config.data_cube_out_channel; out_ch_idx++) {
		for(uint out_h_idx = 0; out_h_idx < pool_config.data_cube_out_height; out_h_idx++) {
			for(uint out_w_idx = 0; out_w_idx < pool_config.data_cube_out_width; out_w_idx++) {
				/* Pooling window coverage on input data plane */
				int win_h_start(out_h_idx * pool_config.filter_stride - pool_config.zero_padding);
				int win_w_start(out_w_idx * pool_config.filter_stride - pool_config.zero_padding);
				int win_h_end  (win_h_start + pool_config.filter_width);
				int win_w_end  (win_w_start + pool_config.filter_width);

				int temp_data;
				switch(pool_config.pool_function) {
				case is_maximum:
					temp_data = std::numeric_limits<int>::lowest();
				case is_average:
					temp_data = 0;
					break;
				case is_minimum:
					temp_data = std::numeric_limits<int>::max();
					break;
				default: assert(0 && "Pooling Engine hasn't support this function yet.");
				}

				for(int in_h_idx = win_h_start; in_h_idx < win_h_end; in_h_idx++) {
					for(int in_w_idx = win_w_start; in_w_idx < win_w_end; in_w_idx++) {
						if((in_h_idx < 0) || (in_h_idx >= pool_config.data_cube_in_height)
							|| (in_w_idx < 0) || (in_w_idx >= pool_config.data_cube_in_width)) {
							switch(pool_config.pool_function) {
							case is_maximum:
								if(0 > temp_data) temp_data = 0.0;
								break;
							case is_average:
								break;
							case is_minimum:
								if(0 < temp_data) temp_data = 0.0;
								break;
							default: assert(0 && "Pooling Engine hasn't support this function yet.");
							}
						} else {
							int data_in_idx(out_ch_idx * pool_config.data_cube_in_height * pool_config.data_cube_in_width
							                + in_h_idx * pool_config.data_cube_in_width + in_w_idx);
							int mem_r_data(pool_config.data_in_ptr[data_in_idx]);

							switch(pool_config.pool_function) {
							case is_maximum:
								if(mem_r_data > temp_data) temp_data = mem_r_data;
								break;
							case is_average:
								temp_data += mem_r_data;
								break;
							case is_minimum:
								if(mem_r_data < temp_data) temp_data = mem_r_data;
								break;
							default: assert(0 && "Pooling Engine hasn't support this function yet.");
							}
						}
					}
				}

				uint window_size(pool_config.filter_width * pool_config.filter_width);
				switch(pool_config.pool_function) {
				case is_maximum:
				case is_minimum:
					break;
				case is_average:
					temp_data = temp_data / window_size;
					break;
				default: assert(0 && "Pooling Engine hasn't support this function yet.");
				}

				int data_out_idx(out_ch_idx * pool_config.data_cube_out_height * pool_config.data_cube_out_width
				                 + out_h_idx * pool_config.data_cube_out_width + out_w_idx);
				pool_config.data_out_ptr[data_out_idx] = temp_data;
			}
		}
	}
}
