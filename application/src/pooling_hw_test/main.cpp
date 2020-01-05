#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cassert>

#include "ctrler_api/ctrler_api.h"

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
                control_hw_pool();
        }

        barrier(barr);

        cout << "\n##########################\n"
             << "# Leaving RISC-V process " << get_id() << "\n"
             << "##########################" << endl;

        barrier(barr);

}

void GenTestData(int* data, const int data_num) {
	for(int i = 0; i < data_num; i++) {
		int ran = std::rand() % 256;
		data[i] = ran;
	}
}

void PrintData(int* data, const int channel, const int height, const int width) {
	for(int i = 0; i < channel; i++) {
		cout << "Channel #" << i << '\n';
		for(int j = 0; j < height; j++) {
			for(int k = 0; k < width; k++) {
				int index(i * height * width + j * width + k);
				cout << std::fixed << std::setw(8) << std::setprecision(2) << data[index];
			}
			cout << '\n';
		}
		cout << '\n';
	}
	cout << endl;
}

void control_hw_pool() {
	const int data_in_channel = 2;
	const int data_in_height = 5;
	const int data_in_width = 5;

	const int filter_width = 3;
	const int filter_stride = 1;
	const int zero_padding = 0;

	const int data_out_width  = ((data_in_height + 2 * zero_padding) - filter_width) / filter_stride + 1;
	const int data_out_height = data_out_width;
	const int data_out_channel = data_in_channel;

	const int input_size = data_in_channel * data_in_height * data_in_width;
	const int output_size = data_out_channel * data_out_height * data_out_width;
	const int data_in_address = POOL_BUFFER_ADDRESS;
	const int data_out_address = data_in_address + input_size * sizeof(int);

	ControllerAPI ctrl_api;
	ePoolFunction function = is_maximum;

	cout << "[Test information]\n"
	     << "        Pooling function: ";
	switch(function) {
		case is_maximum: cout << "maximum"; break;
		case is_average: cout << "average"; break;
		case is_minimum: cout << "minimum"; break;
		default: assert(0 && "This pooling function hasn't been supported yet.");
	}
	cout << '\n'
	     << "               Data type: floating point 32\n"
	     << "    Input data dimension: " << data_in_channel
	                                     << " x " << data_in_height 
	                                     << " x " << data_in_width << '\n'
	     << "            Zero Padding: " << zero_padding << '\n'
	     << "     Pooling window size: " << filter_width
	                                     << " x " << filter_width << '\n'
	     << "   Pooling window stride: " << filter_stride << '\n'
	     << "   Output data dimension: " << data_out_channel
	                                     << " x " << data_out_height
	                                     << " x " << data_out_width << '\n' << endl;

	/* Generate random test data then load them into RAM through debug transport (no timing effort) */
	int* test_data = new int[input_size];
	GenTestData(test_data, input_size);

	cout << "Test data cube:" << endl;
	PrintData(test_data, data_in_channel, data_in_height, data_in_width);

        ctrl_api.DebugWriteData(GLOBAL_BUFFER_ADDRESS, (unsigned char*)test_data, input_size * sizeof(int));

	/* Configure DMA to load test data into buffer from RAM */
	vector<ChannelConfig> dma_config(1);
	dma_config[0].channel_enable  = 1;
	dma_config[0].source_address  = GLOBAL_BUFFER_ADDRESS;
	dma_config[0].dest_address    = data_in_address;
	dma_config[0].transfer_length = input_size * sizeof(int);
	dma_config[0].transfer_type   = 3;
	dma_config[0].line_length     = 0;
	dma_config[0].line_stride     = 0;

	// write reg interface
	ctrl_api.ConfigDMA(is_pool_dma, dma_config);
	// start DMA
	ctrl_api.SetOPEnable(is_pool_dma);
	// wait DMA done
	while(ctrl_api.ReadStatus(is_pool_dma) != 0) {}
	// clear the enable reg
	ctrl_api.ClearDMAOPEnable(is_pool_dma);
	

	//PrintData(data_in_address, data_in_channel, data_in_height, data_in_width);

	/* Configure pooling engine to process test data */
        ctrl_api.ProgramPoolReg(function, is_float32,
        	data_in_address, data_out_address,
        	data_in_channel, data_in_height, data_in_width,
        	data_out_channel, data_out_height, data_out_width,
        	filter_width, filter_stride, zero_padding);

	// start Pool
	ctrl_api.SetOPEnable(is_pool_engine);
	// wait Pool done
	while(ctrl_api.ReadStatus(is_pool_engine) != 0) {}

	/* Configure DMA to move results from buffer into RAM */
	dma_config[0].channel_enable  = 1;
	dma_config[0].source_address  = data_out_address;
	dma_config[0].dest_address    = GLOBAL_BUFFER_ADDRESS;
	dma_config[0].transfer_length = output_size * sizeof(int);
	dma_config[0].transfer_type   = 3;
	dma_config[0].line_length     = 0;
	dma_config[0].line_stride     = 0;

	// write reg interface
	ctrl_api.ConfigDMA(is_pool_dma, dma_config);
	// start DMA
	ctrl_api.SetOPEnable(is_pool_dma);
	// wait DMA done
	while(ctrl_api.ReadStatus(is_pool_dma) != 0) {}
	// clear the enable reg
	ctrl_api.ClearDMAOPEnable(is_pool_dma);

	/* Get result from RAM through debug transport (no timing effort) */
	int* result = new int[output_size];
        ctrl_api.DebugReadData(GLOBAL_BUFFER_ADDRESS, (unsigned char*)result, output_size * sizeof(int));

	cout << "Result cube:" << endl;
	PrintData(result, data_out_channel, data_out_height, data_out_width);
	
	if(test_data) delete[] test_data;
	if(result) delete[] result;

}
