#pragma once

#include <scml2.h>
#include <systemc>
#include <tlm>
#include "tlm_utils/simple_target_socket.h"

class ScmlBridge : public sc_module {
public:
	/* Constructor */
	SC_HAS_PROCESS(ScmlBridge);
	ScmlBridge(const sc_module_name &name,
	           unsigned long long base_address = 0);

	/* Destructor */
	~ScmlBridge();

	/* Port list */
	tlm_utils::simple_target_socket<ScmlBridge> t_socket;
	scml2::initiator_socket<32> i_socket;

private:
	unsigned long long base_address;
	void b_transport(tlm::tlm_generic_payload &payload, sc_core::sc_time &delay);
};
