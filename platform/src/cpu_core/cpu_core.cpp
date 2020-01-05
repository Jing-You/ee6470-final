#include "cpu_core.h"

CpuCore::CpuCore(const sc_module_name &name) :
	sc_core::sc_module(name),
	cpu("cpu"),
	tile_bus("tile_bus"),
	program_stack_ram("program_stack_ram", "t_socket", PROGRAM_STACK_RAM_SIZE - 1),
	local_bus_bridge("local_bus_bridge"),
	global_bus_bridge("global_bus_bridge"),
	local_i_socket(local_bus_bridge.i_socket),
	global_i_socket(global_bus_bridge.i_socket)
{
	/* Connect CPU and tile bus */
	cpu.DM.i_socket(tile_bus.target_socket[0]);

	/* Connect program_stack memory and tile bus */
	tile_bus.bindTargetSocket(program_stack_ram.sp1,
	                          PROGRAM_STACK_RAM_ADDRESS,
	                          PROGRAM_STACK_RAM_ADDRESS + PROGRAM_STACK_RAM_SIZE - 1,
	                          PROGRAM_STACK_RAM_SIZE - 1
	                         );

	/* Connect accelerator bus bridge and tile bus */
	tile_bus.bindTargetSocket(local_bus_bridge.t_socket,
	                          ACC_START_ADDRESS,
	                          ACC_END_ADDRESS
	                         );

	/* Connect main system bus bridge and tile bus for debugging */
	tile_bus.bindTargetSocket(global_bus_bridge.t_socket,
	                          SHARED_MEM_ADDRESS,
	                          static_cast<unsigned long long>(SHARED_MEM_ADDRESS) + SHARED_MEM_SIZE - 1
	                         );
}

CpuCore::~CpuCore() {}
