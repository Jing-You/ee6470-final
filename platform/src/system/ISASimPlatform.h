#pragma once

#include <scml2.h>
#include <systemc>
#include <tlm>
#include "cpu_core/cpu_core.h"
//#include "AccPlatform.h"

class ISASimPlatform : public sc_module {
public:
	/* Constructor */
	SC_HAS_PROCESS(ISASimPlatform);
	ISASimPlatform(const sc_module_name &name);

	/* Destructor */
	~ISASimPlatform();

public:
	CpuCore controller;

private:
	//AccPlatform platform;

	/* Port list */
	tlm::tlm_target_socket<32> ctrler_local_t_socket;
	tlm::tlm_target_socket<32> ctrler_global_t_socket;

public:
	/* Port adaptor list */
	scml2::tlm2_gp_target_adapter<32> ctrler_local_t_adapter;
	scml2::tlm2_gp_target_adapter<32> ctrler_global_t_adapter;
};
