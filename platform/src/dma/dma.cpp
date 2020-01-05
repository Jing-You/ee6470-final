#include "dma.h"

DMA::DMA(const sc_module_name &name,
         eDMAType type,
         unsigned long long local_start_address,
         unsigned long long local_end_address) :
	sc_module(name),
	global_i_socket("global_i_socket"),
	local_i_socket("local_i_socket"),
	config_reg("config_reg", (1 + DMA_CHANNEL_NUM) * 16),
	status    ("status", config_reg,  0),
	mode      ("mode",   config_reg,  1),
	type(type),
	local_start_address(local_start_address),
	local_end_address(local_end_address),
	dma_period(DMA_PERIOD, SC_NS)
{
	/* Initialization */
	config_reg.initialize(0);
	for(int i = 0; i < DMA_CHANNEL_NUM; i++) {
		channel_enable[i]  = new scml2::reg<uint>("channel_enable_" + to_string(i),  config_reg, 16 * (i + 1));
		source_address[i]  = new scml2::reg<uint>("source_address_" + to_string(i),  config_reg, 16 * (i + 1) + 1);
		dest_address[i]    = new scml2::reg<uint>("dest_address_" + to_string(i),    config_reg, 16 * (i + 1) + 2);
		transfer_length[i] = new scml2::reg<uint>("transfer_length_" + to_string(i), config_reg, 16 * (i + 1) + 3);
		transfer_type[i]   = new scml2::reg<uint>("transfer_type_" + to_string(i),   config_reg, 16 * (i + 1) + 4);
		line_length[i]     = new scml2::reg<uint>("line_length_" + to_string(i),     config_reg, 16 * (i + 1) + 5);
		line_stride[i]     = new scml2::reg<uint>("line_stride_" + to_string(i),     config_reg, 16 * (i + 1) + 6);
	}

	/* Callback registrations */
	set_word_write_callback(mode, SCML2_CALLBACK(WriteMode), scml2::NEVER_SYNCING);

	cout << this->name() << " has been instantiated.\n"
	     << "[Information]\n"
	     << "           Local address space: 0x" << hex << local_start_address << " ~ 0x" << local_end_address << dec << '\n'
	     << "              Operating period: " << dma_period << '\n' << endl;

	SC_THREAD(DMAThread0);
	SC_THREAD(DMAThread1);
	SC_THREAD(DMAThread2);
	SC_THREAD(DMAThread3);
	SC_THREAD(DMAThread4);
	SC_THREAD(DMAThread5);
	SC_THREAD(DMAThread6);
	SC_THREAD(DMAThread7);
	SC_THREAD(DMAThread8);
	SC_THREAD(DMAThread9);
	SC_THREAD(DMAThread10);
	SC_THREAD(DMAThread11);
	SC_THREAD(DMAThread12);
	SC_THREAD(DMAThread13);
	SC_THREAD(DMAThread14);
	SC_THREAD(DMAThread15);
}

DMA::~DMA() {
	for(int i = 0; i < DMA_CHANNEL_NUM; i++) {
		if(channel_enable[i])  delete channel_enable[i];
		if(source_address[i])  delete source_address[i];
		if(dest_address[i])    delete dest_address[i];
		if(transfer_length[i]) delete transfer_length[i];
		if(transfer_type[i])   delete transfer_type[i];
		if(line_length[i])     delete line_length[i];
		if(line_stride[i])     delete line_stride[i];
	}
}

void DMA::DMAThread0() {
	ChannelThread(0);
}

void DMA::DMAThread1() {
	ChannelThread(1);
}

void DMA::DMAThread2() {
	ChannelThread(2);
}

void DMA::DMAThread3() {
	ChannelThread(3);
}

void DMA::DMAThread4() {
	ChannelThread(4);
}

void DMA::DMAThread5() {
	ChannelThread(5);
}

void DMA::DMAThread6() {
	ChannelThread(6);
}

void DMA::DMAThread7() {
	ChannelThread(7);
}

void DMA::DMAThread8() {
	ChannelThread(8);
}

void DMA::DMAThread9() {
	ChannelThread(9);
}

void DMA::DMAThread10() {
	ChannelThread(10);
}

void DMA::DMAThread11() {
	ChannelThread(11);
}

void DMA::DMAThread12() {
	ChannelThread(12);
}

void DMA::DMAThread13() {
	ChannelThread(13);
}

void DMA::DMAThread14() {
	ChannelThread(14);
}

void DMA::DMAThread15() {
	ChannelThread(15);
}

void DMA::ChannelThread(int ch_index) {
	while(true) {
		while((mode != 1) || !*channel_enable[ch_index]) {
			wait(event_dma_start);
		}
		status = status ^ (1 << ch_index);
		DoDMA(ch_index);
		status = status ^ (1 << ch_index);
	}	
}

void DMA::PrintConfigReg() const {
	cout << "== " << this->name() << "\'s config registers ==\n"
	     << "[Common]\n"
	     << "            status = "   << status << '\n'
	     << "              mode = "   << mode << '\n';
	for(int i = 0; i < DMA_CHANNEL_NUM; i++) {
		cout << "[Channel " << i << "]\n"
		     << "    channel_enable = "   << *channel_enable[i] << '\n'
		     << "    source_address = 0x" << hex << *source_address[i] << '\n'
		     << "      dest_address = 0x" << *dest_address[i] << dec << '\n'
		     << "   transfer_length = "   << *transfer_length[i] << '\n'
		     << "     transfer_type = "   << *transfer_type[i] << '\n'
		     << "       line_length = "   << *line_length[i] << '\n'
		     << "       line_stride = "   << *line_stride[i] << '\n';
	}
	cout << "== End ==\n" << endl;
}

void DMA::DoDMA(int ch_index) {
	cout << "= " << sc_time_stamp().to_string() << " =\n"
	     << "== " << this->name() << " starts transferring data ==\n\n";
#ifdef DEBUG
	PrintConfigReg();
#endif
	int i = ch_index;
	if(*channel_enable[i] == 1) {
		bool is_global_write((*source_address[i] >= local_start_address) && (*source_address[i] <= local_end_address));
		bool is_global_read((*dest_address[i] >= local_start_address) && (*dest_address[i] <= local_end_address));

		unsigned char* dma_buffer(nullptr);
		unsigned long long local_address(0);
		unsigned long long global_address(0);
		uint burst_beat_num(0);

		if(is_global_write) {
			switch(type) {
			case is_engine_type:
				local_address = *source_address[i] - local_start_address;
				break;
			case is_bridge_type:
				local_address = *source_address[i];
				break;
			default: assert(0 && "DMA doesn't support this DMA type.");
			}
			global_address = *dest_address[i];
			if(*line_length[i] == 0) {
				/* 1D tranfer */
				dma_buffer = new unsigned char[*transfer_length[i]];
				local_i_socket.read<unsigned char>(local_address, dma_buffer, *transfer_length[i]);
				global_i_socket.write<unsigned char>(global_address, dma_buffer, *transfer_length[i]);

				burst_beat_num = ceil(static_cast<float>(*transfer_length[i]) / BUS_WIDTH) - 1;
				wait(burst_beat_num * dma_period);
			} else {
				/* 2D tranfer */
				dma_buffer = new unsigned char[*line_length[i]];
				for(uint j = 0; j < *transfer_length[i]; j += *line_length[i]) {
					local_i_socket.read<unsigned char>(local_address, dma_buffer, *line_length[i]);
					global_i_socket.write<unsigned char>(global_address, dma_buffer, *line_length[i]);
					local_address  += *line_stride[i];
					global_address += *line_length[i];

					burst_beat_num = ceil(static_cast<float>(*line_length[i]) / BUS_WIDTH) - 1;
					wait(burst_beat_num * dma_period);
				}
			}
		} else if(is_global_read) {
			switch(type) {
			case is_engine_type:
				local_address  = *dest_address[i] - local_start_address;
				break;
			case is_bridge_type:
				local_address  = *dest_address[i];
				break;
			default: assert(0 && "DMA doesn't support this DMA type.");
			}
			global_address = *source_address[i];
			if(*line_length[i] == 0) {
				/* 1D tranfer */
				dma_buffer = new unsigned char[*transfer_length[i]];
				global_i_socket.read<unsigned char>(global_address, dma_buffer, *transfer_length[i]);
				local_i_socket.write<unsigned char>(local_address, dma_buffer, *transfer_length[i]);

				burst_beat_num = ceil(static_cast<float>(*transfer_length[i]) / BUS_WIDTH) - 1;
				wait(burst_beat_num * dma_period);
			} else {
				/* 2D tranfer */
				dma_buffer = new unsigned char[*line_length[i]];
				for(uint j = 0; j < *transfer_length[i]; j += *line_length[i]) {
					global_i_socket.read<unsigned char>(global_address, dma_buffer, *line_length[i]);
					local_i_socket.write<unsigned char>(local_address, dma_buffer, *line_length[i]);
					global_address += *line_stride[i];
					local_address  += *line_length[i];

					burst_beat_num = ceil(static_cast<float>(*line_length[i]) / BUS_WIDTH) - 1;
					wait(burst_beat_num * dma_period);
				}
			}
		} else
			assert(0 && "DMA operation error.");
		if(dma_buffer) delete[] dma_buffer;

		*channel_enable[i] = 0;
	}

	cout << "= " << sc_time_stamp().to_string() << " =\n"
	     << "== " << this->name() << " finishes transferring data ==\n" << endl;
}

bool DMA::WriteMode(const uint &dma_mode) {
	mode = dma_mode;
	if(dma_mode == 1) event_dma_start.notify(SC_ZERO_TIME);

	return true;
}

