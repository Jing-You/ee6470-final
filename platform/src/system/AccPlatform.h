#pragma once

#include <scml2.h>
#include <systemc>
#include <tlm>

#include "common/config.h"
#include "pool_engine/pool_engine.h"
#include "lock_engine/lock.h"
#include "dma/dma.h"
#include "memory/memory_model.h"

class AccPlatform : public sc_module {
public:
	/* Constructor */
	SC_HAS_PROCESS(AccPlatform);
	AccPlatform(const sc_module_name &name);

	/* Destructor */
	~AccPlatform();

private:
	/* Port list */
	tlm::tlm_target_socket<32> bridge_dma_local_t_socket;
	tlm::tlm_target_socket<32> bridge_dma_global_t_socket;
	tlm::tlm_target_socket<32> lock_local_t_socket;
	tlm::tlm_target_socket<32> lock_global_t_socket;
	tlm::tlm_target_socket<32> pool_dma_t_socket;

	/* Port adaptor list */
	scml2::tlm2_gp_target_adapter<32> bridge_dma_local_t_adapter;
	scml2::tlm2_gp_target_adapter<32> bridge_dma_global_t_adapter;
	scml2::tlm2_gp_target_adapter<32> lock_local_t_adapter;
	scml2::tlm2_gp_target_adapter<32> lock_global_t_adapter;
	scml2::tlm2_gp_target_adapter<32> pool_dma_t_adapter;

	/* Engines */
	PoolEngine pool_engine;
	Lock_engine lock;

	/* DMAs */
	DMA bridge_dma;
	DMA pool_dma;

	/* Memory */
	MemoryModel<unsigned char> dram;
	MemoryModel<unsigned char> global_buffer;

public:
	/* Interconnect */
	scml2::router<uint> system_bus;
	scml2::router<uint> local_bus;
};
