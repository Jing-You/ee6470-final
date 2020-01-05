#include "pool_engine.h"

PoolEngine::PoolEngine(const sc_module_name &name) :
	sc_module(name),
	t_socket("t_socket"),
	t_adapter("t_adapter", t_socket),
	pool_period(POOL_PERIOD, SC_NS),
	cb_reg_set("cb_reg_set", POOL_SINGLE_REG_NUM + POOL_DOUBLE_REG_NUM),
	cb_s_status               ("cb_s_status",                cb_reg_set, 0),
	cb_s_config_ready         ("cb_s_config_ready",          cb_reg_set, 1),
	cb_s_pointer              ("cb_s_pointer",               cb_reg_set, 2),
	cb_d_op_enable            ("cb_d_op_enable",             cb_reg_set, 3),
	cb_d_misc_config          ("cb_d_misc_config",           cb_reg_set, 4),
	cb_d_data_type            ("cb_d_data_type",             cb_reg_set, 5),
	cb_d_data_in_address      ("cb_d_data_in_address",       cb_reg_set, 6),
	cb_d_data_out_address     ("cb_d_data_out_address",      cb_reg_set, 7),
	cb_d_data_cube_in_width   ("cb_d_data_cube_in_width",    cb_reg_set, 8),
	cb_d_data_cube_in_height  ("cb_d_data_cube_in_height",   cb_reg_set, 9),
	cb_d_data_cube_in_channel ("cb_d_data_cube_in_channel",  cb_reg_set, 10),
	cb_d_data_cube_out_widhth ("cb_d_data_cube_out_widhth",  cb_reg_set, 11),
	cb_d_data_cube_out_height ("cb_d_data_cube_out_height",  cb_reg_set, 12),
	cb_d_data_cube_out_channel("cb_d_data_cube_out_channel", cb_reg_set, 13),
	cb_d_filter_width         ("cb_d_filter_width",          cb_reg_set, 14),
	cb_d_filter_stride        ("cb_d_filter_stride",         cb_reg_set, 15),
	cb_d_zero_padding         ("cb_d_zero_padding",          cb_reg_set, 16),
	eg_reg_set(POOL_SINGLE_REG_NUM + POOL_DOUBLE_REG_NUM),
	eg_s_status               (eg_reg_set[0]),
	eg_s_config_ready         (eg_reg_set[1]),
	eg_s_pointer              (eg_reg_set[2]),
	eg_d_op_enable            (eg_reg_set[3]),
	eg_d_misc_config          (eg_reg_set[4]),
	eg_d_data_type            (eg_reg_set[5]),
	eg_d_data_in_address      (eg_reg_set[6]),
	eg_d_data_out_address     (eg_reg_set[7]),
	eg_d_data_cube_in_width   (eg_reg_set[8]),
	eg_d_data_cube_in_height  (eg_reg_set[9]),
	eg_d_data_cube_in_channel (eg_reg_set[10]),
	eg_d_data_cube_out_widhth (eg_reg_set[11]),
	eg_d_data_cube_out_height (eg_reg_set[12]),
	eg_d_data_cube_out_channel(eg_reg_set[13]),
	eg_d_filter_width         (eg_reg_set[14]),
	eg_d_filter_stride        (eg_reg_set[15]),
	eg_d_zero_padding         (eg_reg_set[16]),
	double_reg_set(POOL_DOUBLE_REG_NUM, POOL_SINGLE_REG_NUM),
	data_buffer("data_buffer", POOL_BUFFER_SIZE)
{
	/* Initialize */
	UpdateCBRegSet();
	UpdateEgRegSet();
	data_buffer.initialize(0);

	/* Callback registrations */
	set_word_read_callback (cb_s_status,       SCML2_CALLBACK(ReadStatus),    scml2::NEVER_SYNCING);
	set_word_read_callback (cb_s_config_ready, SCML2_CALLBACK(ReadCfgReady),  scml2::NEVER_SYNCING);
	set_word_read_callback (cb_s_pointer,      SCML2_CALLBACK(ReadPtr),       scml2::NEVER_SYNCING);
	set_word_read_callback (cb_d_op_enable,    SCML2_CALLBACK(ReadOPEnable),  scml2::NEVER_SYNCING);
	set_word_write_callback(cb_d_op_enable,    SCML2_CALLBACK(WriteOPEnable), scml2::NEVER_SYNCING);

	t_adapter(data_buffer);

	cout << this->name() << " has been instantiated.\n"
	     << "[Information]\n"
	     << "   Config Register address space: 0x" << hex << POOL_BASE_ADDRESS
	     << " ~ 0x" << POOL_BASE_ADDRESS + (POOL_SINGLE_REG_NUM + POOL_DOUBLE_REG_NUM) * sizeof(uint) - 1 << dec << '\n'
	     << "          Single group registers: " << POOL_SINGLE_REG_NUM << '\n'
	     << "          Double group registers: " << POOL_DOUBLE_REG_NUM << '\n'
	     << "                Operating period: " << pool_period << '\n' << endl;

	SC_THREAD(PoolEngineThread);
}

void PoolEngine::PoolEngineThread() {
	while(true) {
		while(double_reg_set.GetOPEnable() != 1) {
			wait(event_reg_op_enable);
		}
		double_reg_set.SetStatusReg(0x1);
		UpdateEgRegSet();
		DoPooling();
		double_reg_set.SetStatusReg(0x0);
		double_reg_set.ClearOPEnable();
	}
}

bool PoolEngine::ReadStatus(uint &status) {
	sc_uint<32> new_status(0);
	double_reg_set.CBGetReadable(0, new_status);
	cb_s_status = new_status.to_uint();
	status      = new_status.to_uint();

	return true;
}

bool PoolEngine::ReadCfgReady(uint &ready) {
	sc_uint<32> config_ready(0);
	double_reg_set.CBGetReadable(1, config_ready);
	cb_s_config_ready = config_ready.to_uint();
	ready             = config_ready.to_uint();

	return true;
}

bool PoolEngine::ReadPtr(uint &ptr) {
	sc_uint<32> pointer(0);
	double_reg_set.CBGetReadable(2, pointer);
	cb_s_pointer = pointer.to_uint();
	ptr          = pointer.to_uint();

	return true;
}

bool PoolEngine::ReadOPEnable(uint &enable) {
	sc_uint<32> op_enable(0);
	double_reg_set.CBGetReadable(POOL_SINGLE_REG_NUM, op_enable);
	cb_d_op_enable = op_enable.to_uint();
	enable         = op_enable.to_uint();

	return true;
}

bool PoolEngine::WriteOPEnable(const uint &enable) {
	if(enable == 1) {
		cb_d_op_enable = 1;

		for(uint i = POOL_SINGLE_REG_NUM; i < POOL_SINGLE_REG_NUM + POOL_DOUBLE_REG_NUM; i++) {
			sc_uint<32> data(cb_reg_set[i]);
			double_reg_set.CBSetWritable(i, data);
		}
		
		double_reg_set.CBSetOPEnable();
		event_reg_op_enable.notify(SC_ZERO_TIME);
		UpdateCBRegSet();
	}

	return true;
}

void PoolEngine::UpdateCBRegSet() {
	sc_uint<32> data(0);
	for(uint i = 0; i < POOL_SINGLE_REG_NUM + POOL_DOUBLE_REG_NUM; i++) {
		double_reg_set.CBGetReadable(i, data);
		cb_reg_set[i] = data.to_uint();
	}
}


void PoolEngine::UpdateEgRegSet() {
	for(uint i = 0; i < POOL_SINGLE_REG_NUM + POOL_DOUBLE_REG_NUM; i++)
		double_reg_set.EgGetReadable(i, eg_reg_set[i]);
}

void PoolEngine::PrintCBRegSet() const{
	cout << "== " << this->name() << " ==\n"
	     << "[Config bus view]\n"
	     << "                  cb_s_status = " << cb_s_status << '\n'
	     << "            cb_s_config_ready = " << cb_s_config_ready << '\n'
	     << "                 cb_s_pointer = " << cb_s_pointer << '\n'
	     << "               cb_d_op_enable = " << cb_d_op_enable << '\n'
	     << "             cb_d_misc_config = " << cb_d_misc_config << '\n'
	     << "               cb_d_data_type = " << cb_d_data_type << '\n'
	     << "         cb_d_data_in_address = " << cb_d_data_in_address << '\n'
	     << "        cb_d_data_out_address = " << cb_d_data_out_address << '\n'
	     << "      cb_d_data_cube_in_width = " << cb_d_data_cube_in_width << '\n'
	     << "     cb_d_data_cube_in_height = " << cb_d_data_cube_in_height << '\n'
	     << "    cb_d_data_cube_in_channel = " << cb_d_data_cube_in_channel << '\n'
	     << "    cb_d_data_cube_out_widhth = " << cb_d_data_cube_out_widhth << '\n'
	     << "    cb_d_data_cube_out_height = " << cb_d_data_cube_out_height << '\n'
	     << "   cb_d_data_cube_out_channel = " << cb_d_data_cube_out_channel << '\n'
	     << "            cb_d_filter_width = " << cb_d_filter_width << '\n'
	     << "           cb_d_filter_stride = " << cb_d_filter_stride << '\n'
	     << "            cb_d_zero_padding = " << cb_d_zero_padding << '\n'
	     << "== End ==\n" << endl;
}

void PoolEngine::PrintEgRegSet() const{
	cout << "== " << this->name() << " ==\n"
	     << "[Engine view]\n"
	     << "                  eg_s_status = " << eg_s_status.to_string(SC_HEX) << '\n'
	     << "            eg_s_config_ready = " << eg_s_config_ready.to_string(SC_HEX) << '\n'
	     << "                 eg_s_pointer = " << eg_s_pointer.to_string(SC_HEX) << '\n'
	     << "               eg_d_op_enable = " << eg_d_op_enable.to_string(SC_HEX) << '\n'
	     << "             eg_d_misc_config = " << eg_d_misc_config.to_string(SC_HEX) << '\n'
	     << "               eg_d_data_type = " << eg_d_data_type.to_string(SC_HEX) << '\n'
	     << "         eg_d_data_in_address = " << eg_d_data_in_address.to_string(SC_HEX) << '\n'
	     << "        eg_d_data_out_address = " << eg_d_data_out_address.to_string(SC_HEX) << '\n'
	     << "      eg_d_data_cube_in_width = " << eg_d_data_cube_in_width.to_string(SC_HEX) << '\n'
	     << "     eg_d_data_cube_in_height = " << eg_d_data_cube_in_height.to_string(SC_HEX) << '\n'
	     << "    eg_d_data_cube_in_channel = " << eg_d_data_cube_in_channel.to_string(SC_HEX) << '\n'
	     << "    eg_d_data_cube_out_widhth = " << eg_d_data_cube_out_widhth.to_string(SC_HEX) << '\n'
	     << "    eg_d_data_cube_out_height = " << eg_d_data_cube_out_height.to_string(SC_HEX) << '\n'
	     << "   eg_d_data_cube_out_channel = " << eg_d_data_cube_out_channel.to_string(SC_HEX) << '\n'
	     << "            eg_d_filter_width = " << eg_d_filter_width.to_string(SC_HEX) << '\n'
	     << "           eg_d_filter_stride = " << eg_d_filter_stride.to_string(SC_HEX) << '\n'
	     << "            eg_d_zero_padding = " << eg_d_zero_padding.to_string(SC_HEX) << '\n'
	     << "== End ==\n" << endl;
}

void PoolEngine::DoPooling() {
	cout << "= " << sc_time_stamp().to_string() << " =\n"
	     << "== " << this->name() << " starts doing pooling ==\n\n";
#ifdef DEBUG
	PrintEgRegSet();
#endif

	/* Still can update status accoding to working status while doing pooling */
	ePoolFunction pool_function(static_cast<ePoolFunction>(eg_d_misc_config(1, 0).to_uint()));
	eDataType pool_data_type   (static_cast<eDataType>(eg_d_data_type(3, 0).to_uint()));
	uint data_in_address       (eg_d_data_in_address(19, 0).to_uint());
	uint data_out_address      (eg_d_data_out_address(19, 0).to_uint());
	uint data_in_width         (eg_d_data_cube_in_width.to_uint());
	uint data_in_height        (eg_d_data_cube_in_height.to_uint());
	uint data_in_channel       (eg_d_data_cube_in_channel.to_uint());
	uint data_out_width        (eg_d_data_cube_out_widhth.to_uint());
	uint data_out_height       (eg_d_data_cube_out_height.to_uint());
	uint data_out_channel      (eg_d_data_cube_out_channel.to_uint());
	uint filter_width          (eg_d_filter_width.to_uint());
	uint filter_stride         (eg_d_filter_stride.to_uint());
	uint zero_padding          (eg_d_zero_padding.to_uint());

	int data_length(GetDataTypeLength(pool_data_type)); /* in bytes */

	HWDataType ZERO;
	double d_zero(0.0);
	ZERO.Set<double>(pool_data_type, d_zero);

	for(uint out_ch_idx = 0; out_ch_idx < data_out_channel; out_ch_idx++) {
		for(uint out_h_idx = 0; out_h_idx < data_out_height; out_h_idx++) {
			for(uint out_w_idx = 0; out_w_idx < data_out_width; out_w_idx++) {
				/* Pooling window coverage on input data plane */
				int win_h_start(out_h_idx * filter_stride - zero_padding);
				int win_w_start(out_w_idx * filter_stride - zero_padding);
				int win_h_end  (win_h_start + filter_width);
				int win_w_end  (win_w_start + filter_width);
				
				HWDataType temp_data(pool_data_type);
				switch(pool_function) {
				case is_maximum:
					temp_data.SetMinValue();
					break;
				case is_average:
					temp_data.SetBitVec(pool_data_type, 0);
					break;
				case is_minimum:
					temp_data.SetMaxValue();
					break;
				default: assert(0 && "Pooling Engine hasn't support this function yet.");
				}

				for(int in_h_idx = win_h_start; in_h_idx < win_h_end; in_h_idx++) {
					for(int in_w_idx = win_w_start; in_w_idx < win_w_end; in_w_idx++) {
						if((in_h_idx < 0) || (in_h_idx >= static_cast<int>(data_in_height))
							|| (in_w_idx < 0) || (in_w_idx >= static_cast<int>(data_in_width))) {
							switch(pool_function) {
							case is_maximum:
								if(ZERO > temp_data) temp_data = ZERO;
								break;
							case is_average:
								break;
							case is_minimum:
								if(ZERO < temp_data) temp_data = ZERO;
								break;
							default: assert(0 && "Pooling Engine hasn't support this function yet.");
							}
						} else {
							int data_in_offset(out_ch_idx * data_in_height * data_in_width
							                   + in_h_idx * data_in_width + in_w_idx);
							uint mem_r_data(0);
							data_buffer.get(data_in_address + data_in_offset * data_length,
							                reinterpret_cast<unsigned char*>(&mem_r_data),
							                data_length);

							HWDataType mem_data;
							mem_data.SetBitVec(pool_data_type, mem_r_data);
							switch(pool_function) {
							case is_maximum:
								if(mem_data > temp_data) temp_data = mem_data;
								break;
							case is_average:
								temp_data += mem_data;
								break;
							case is_minimum:
								if(mem_data < temp_data) temp_data = mem_data;
								break;
							default: assert(0 && "Pooling Engine hasn't support this function yet.");
							}
						}
					}
				}

				uint window_size(filter_width * filter_width);
				HWDataType pool_size;
				switch(pool_function) {
				case is_maximum:
				case is_minimum:
					break;
				case is_average:
					pool_size.Set<uint>(pool_data_type, window_size);
					temp_data = temp_data / pool_size;
					break;
				default: assert(0 && "Pooling Engine hasn't support this function yet.");
				}

				uint mem_w_data(0);
				mem_w_data = temp_data.to_uint();
				int data_out_offset = out_ch_idx * data_out_height * data_out_width
				                      + out_h_idx * data_out_width + out_w_idx;
				data_buffer.put(data_out_address + data_out_offset * data_length,
				                reinterpret_cast<unsigned char*>(&mem_w_data),
				                data_length);
			}
		}
	}
	wait(data_out_channel * data_out_height * data_out_width * filter_width * filter_width * pool_period);
	
	cout << "= " << sc_time_stamp().to_string() << " =\n"
	     << "== " << this->name() << " finishes doing pooling ==\n" << endl;
}
