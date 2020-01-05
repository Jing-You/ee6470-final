#include "ISASimPlatform.h"

ISASimPlatform::ISASimPlatform(const sc_module_name &name) :
	sc_module(name),
	//platform("AcceleratorPlatform"),
	controller("CPU"),
	ctrler_local_t_socket("ctrler_local_t_socket"),
	ctrler_local_t_adapter("ctrler_local_t_adapter", ctrler_local_t_socket),
	ctrler_global_t_socket("ctrler_global_t_socket"),
	ctrler_global_t_adapter("ctrler_global_t_adapter", ctrler_global_t_socket)
{
	/* Unit-tester / Micro-controller Binding */
	controller.local_i_socket(ctrler_local_t_socket);
	controller.global_i_socket(ctrler_global_t_socket);

	/* Bus Binding */
	//ctrler_local_t_adapter(platform.local_bus);
	//ctrler_global_t_adapter(platform.system_bus);
}

ISASimPlatform::~ISASimPlatform() {}
