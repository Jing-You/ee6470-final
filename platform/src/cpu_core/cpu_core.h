#pragma once

#include <scml2.h>
#include <systemc>

#include "common/config.h"
#include "riscv_rv32g/riscv.H"
#include "simple_bus.h"
#include "tlm_memory.h"
#include "scml_bridge.h"

class CpuCore : public sc_core::sc_module{
public:
	/* Constructor */
	SC_HAS_PROCESS(CpuCore);
	CpuCore(const sc_module_name &name);

	/* Destructor */
	~CpuCore();

public:
	/* Port list */
	scml2::initiator_socket<32>& local_i_socket;
	scml2::initiator_socket<32>& global_i_socket;

	/* ArchC RISC-V */
	riscv cpu;

private:
	/* Components inside the core */
	SimpleBus<1, 3> tile_bus;
	ram program_stack_ram;
	ScmlBridge local_bus_bridge;
	ScmlBridge global_bus_bridge;
};
