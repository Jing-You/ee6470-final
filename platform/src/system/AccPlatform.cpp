#include "AccPlatform.h"

AccPlatform::AccPlatform(const sc_module_name &name) :
	sc_module(name),
	bridge_dma_local_t_socket("bridge_dma_local_t_socket"),
	bridge_dma_local_t_adapter("bridge_dma_local_t_adapter", bridge_dma_local_t_socket),
	bridge_dma_global_t_socket("bridge_dma_global_t_socket"),
	bridge_dma_global_t_adapter("bridge_dma_global_t_adapter", bridge_dma_global_t_socket),
	lock_local_t_socket("lock_local_t_socket"),
	lock_local_t_adapter("lock_local_t_adapter", lock_local_t_socket),
	lock_global_t_socket("lock_global_t_socket"),
	lock_global_t_adapter("lock_global_t_adapter", lock_global_t_socket),
	pool_dma_t_socket("pool_dma_t_socket"),
	pool_dma_t_adapter("pool_dma_t_adapter", pool_dma_t_socket),
	system_bus("system_bus", 0x100000000 / sizeof(uint)), /* size in words (4-byte) */
	local_bus("local_bus", 0x100000000 / sizeof(uint)),
	pool_engine("Pool_Engine"),
	bridge_dma("Bridge_DMA", is_bridge_type, GLOBAL_BUFFER_ADDRESS, GLOBAL_BUFFER_ADDRESS + GLOBAL_BUFFER_SIZE - 1),
	lock("LOCK", is_lock_type, 0x43000000, 0x43001000 - 1),
	pool_dma("Pool_DMA", is_engine_type, POOL_BUFFER_ADDRESS, POOL_BUFFER_ADDRESS + POOL_BUFFER_SIZE - 1),
	global_buffer("Global_Buffer", GLOBAL_BUFFER_SIZE,
	              sc_time(GLOBAL_BUFFER_READ_LATENCY, SC_NS),
	              sc_time(GLOBAL_BUFFER_WRITE_LATENCY, SC_NS)),
	dram("SHARED_MEM", SHARED_MEM_SIZE,
	     sc_time(SHARED_MEM_READ_LATENCY, SC_NS),
	     sc_time(SHARED_MEM_WRITE_LATENCY, SC_NS))
{
	/* Memory map registrations (base address, size, object, offset) in bytes */
	if(!local_bus.map(POOL_BASE_ADDRESS, (POOL_SINGLE_REG_NUM + POOL_DOUBLE_REG_NUM) * sizeof(uint), pool_engine.cb_reg_set, 0))
		assert(0);

	if(!local_bus.map(BRIDGE_DMA_BASE_ADDRESS, (1 + DMA_CHANNEL_NUM) * 16 * sizeof(uint), bridge_dma.config_reg, 0))
		assert(0);

	if(!local_bus.map(0x43000000, 2 * sizeof(uint), lock.config_reg, 0))
		assert(0);

	if(!local_bus.map(POOL_DMA_BASE_ADDRESS, (1 + DMA_CHANNEL_NUM) * 16 * sizeof(uint), pool_dma.config_reg, 0))
		assert(0);

	if(!local_bus.map(GLOBAL_BUFFER_ADDRESS, GLOBAL_BUFFER_SIZE, global_buffer.memory_bank, 0))
		assert(0);

	if(!system_bus.map(SHARED_MEM_ADDRESS, SHARED_MEM_SIZE, dram.memory_bank, 0))
		assert(0);

	/* Debug interface for local buffer */
	if(!local_bus.map(POOL_BUFFER_ADDRESS, POOL_BUFFER_SIZE, pool_engine.data_buffer, 0))
		assert(0);

	bridge_dma_local_t_adapter(local_bus);
	bridge_dma_global_t_adapter(system_bus);
	lock_local_t_adapter(local_bus);
	lock_global_t_adapter(system_bus);

	pool_dma_t_adapter(local_bus);

	/* DMA Binding */
	bridge_dma.global_i_socket(bridge_dma_global_t_socket);
	lock.global_i_socket(lock_global_t_socket);
	pool_dma.global_i_socket(pool_dma_t_socket);

	bridge_dma.local_i_socket(bridge_dma_local_t_socket);
	lock.local_i_socket(lock_local_t_socket);
	pool_dma.local_i_socket(pool_engine.t_socket);
}

AccPlatform::~AccPlatform() {}
