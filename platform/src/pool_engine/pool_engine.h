#ifndef POOL_ENGINE_H
#define POOL_ENGINE_H

#include <scml2.h>
#include <systemc>
#include "reg_set/reg_set.h"
#include "common/config.h"
#include "common/HardwareDataType.h"

class PoolEngine : public sc_module {
public:
	/* Port list */
	tlm::tlm_target_socket<32> t_socket;

	/* Config bus view */
	scml2::memory<uint> cb_reg_set;
	
	/* Local data buffer */
	scml2::memory<ushort> data_buffer;

	/* Constructor */
	SC_HAS_PROCESS(PoolEngine);
	PoolEngine(const sc_module_name &name);

public:
	/* Methods */
	void PrintCBRegSet() const;
	void PrintEgRegSet() const;

private:
	/* Main Thread */
	void PoolEngineThread();

	/* Read callback methods for config register wihch is dynamically changed in time */
	bool ReadStatus(uint &status);
	bool ReadCfgReady(uint &ready);
	bool ReadPtr(uint &ptr);
	bool ReadOPEnable(uint &enable);

	/* Write callback methods for event driven config register */
	bool WriteOPEnable(const uint &enable);

	/* Methods */
	void UpdateCBRegSet();
	void UpdateEgRegSet();
	void DoPooling();

private:
	/* Config bus view aliases */
	scml2::reg<uint> cb_s_status;       /* need read callback */
	scml2::reg<uint> cb_s_config_ready; /* need read callback */
	scml2::reg<uint> cb_s_pointer;      /* need read callback */
	scml2::reg<uint> cb_d_op_enable;    /* need read, write callback */
	scml2::reg<uint> cb_d_misc_config;
	scml2::reg<uint> cb_d_data_type;
	scml2::reg<uint> cb_d_data_in_address;
	scml2::reg<uint> cb_d_data_out_address;
	scml2::reg<uint> cb_d_data_cube_in_width;
	scml2::reg<uint> cb_d_data_cube_in_height;
	scml2::reg<uint> cb_d_data_cube_in_channel;
	scml2::reg<uint> cb_d_data_cube_out_widhth;
	scml2::reg<uint> cb_d_data_cube_out_height;
	scml2::reg<uint> cb_d_data_cube_out_channel;
	scml2::reg<uint> cb_d_filter_width;
	scml2::reg<uint> cb_d_filter_stride;
	scml2::reg<uint> cb_d_zero_padding;

	/* Engine view */
	vector<sc_uint<32>> eg_reg_set;

	/* Engine view aliases */
	sc_uint<32> &eg_s_status;
	sc_uint<32> &eg_s_config_ready;
	sc_uint<32> &eg_s_pointer;
	sc_uint<32> &eg_d_op_enable;
	sc_uint<32> &eg_d_misc_config;
	sc_uint<32> &eg_d_data_type;
	sc_uint<32> &eg_d_data_in_address;
	sc_uint<32> &eg_d_data_out_address;
	sc_uint<32> &eg_d_data_cube_in_width;
	sc_uint<32> &eg_d_data_cube_in_height;
	sc_uint<32> &eg_d_data_cube_in_channel;
	sc_uint<32> &eg_d_data_cube_out_widhth;
	sc_uint<32> &eg_d_data_cube_out_height;
	sc_uint<32> &eg_d_data_cube_out_channel;
	sc_uint<32> &eg_d_filter_width;
	sc_uint<32> &eg_d_filter_stride;
	sc_uint<32> &eg_d_zero_padding;

private:
	/* Port adaptor list */
	scml2::tlm2_gp_target_adapter<32> t_adapter;
	
	Reg_set double_reg_set;
	
	sc_event event_reg_op_enable;

	sc_time pool_period;
};

#endif /*POOL_ENGINE_H*/
