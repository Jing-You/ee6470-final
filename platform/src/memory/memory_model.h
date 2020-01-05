#ifndef MEMORY_MODEL_H
#define MEMORY_MODEL_H

#include <systemc>
// #include <tlm>
#include <scml2.h>
#include "common/config.h"

template <typename T>
class MemoryModel : public sc_module {
public:
	/* Port list */
	// tlm::tlm_target_socket<32> t_socket;

	/* Memory bank */
	scml2::memory<T> memory_bank;

	/* Constructor */
	SC_HAS_PROCESS(MemoryModel);
	MemoryModel(const sc_module_name &name,
	            unsigned long long size,
	            const sc_time &read_latency = sc_time(0, SC_NS),
	            const sc_time &write_latency = sc_time(0, SC_NS));

	/* Destructor */
	~MemoryModel();

private:
	/* Memory bank */
	// scml2::memory<T> memory_bank;

	/* Port adapter */
	// scml2::tlm2_gp_target_adapter<32> t_adapter;
};

#endif /*MEMORY_MODEL_H*/
