#ifndef CONFIG_H
#define CONFIG_H

/* Compiler option */
	// #define DEBUG
	/* About controller APIs generating */
	// #define USING_TLM_SOCKET

/* Common */
#ifdef USING_TLM_SOCKET
	using namespace sc_core;
	using namespace sc_dt;
#endif
	using namespace std;

	enum eDataType     {is_int16 = 6, is_uint16 = 7, is_fixed16 = 8,
	                    is_float16 = 9, is_float32 = 13, none = 16};
	enum eConvMode     {is_basic = 0, is_depth_wise = 1};
	enum eActFunction  {is_relu = 0, is_batch_norm = 6};
	enum ePoolFunction {is_maximum = 0, is_average = 1, is_minimum = 2};
	enum eSubUnit      {is_conv_dma = 0, is_act_dma_0 = 1, is_act_dma_1 = 2,
	                    is_pool_dma = 3,  is_bridge_dma = 4,
	                    is_conv_core = 10, is_act_engine_0 = 11, is_act_engine_1 = 12,
	                    is_pool_engine = 13};
	enum eDMAType      {is_engine_type = 0, is_bridge_type = 1};
	enum eLOCKType      {is_lock_type = 0};

#ifdef USING_TLM_SOCKET
	typedef sc_fixed_fast<16, 8, SC_RND, SC_SAT_ZERO> fixed16;
	typedef sc_int<16> int16;
#endif
	typedef unsigned int uint;

/* Controller's view address map (in bytes)*/
	/* Accelerator address scope */
	#define ACC_START_ADDRESS 0x41000000
	#define ACC_END_ADDRESS   0x47FFFFFF

	/* Bridge DMA */
	#define BRIDGE_DMA_BASE_ADDRESS 0x41000000

	/* Convolution Core */
	#define CONV_DMA_BASE_ADDRESS 0x41100000
	#define CONV_BASE_ADDRESS     0x41200000
	#define CONV_BUFFER_ADDRESS   0x41300000
	
	/* Activation Engine 0 */
	#define ACT_DMA_0_BASE_ADDRESS 0x41400000
	#define ACT_0_BASE_ADDRESS     0x41500000
	#define ACT_BUFFER_0_ADDRESS   0x41600000

	/* Activation Engine 1 */
	#define ACT_DMA_1_BASE_ADDRESS 0x42000000
	#define ACT_1_BASE_ADDRESS     0x42100000
	#define ACT_BUFFER_1_ADDRESS   0x42200000

	/* Pooing Engine */
	#define POOL_DMA_BASE_ADDRESS 0x41700000
	#define POOL_BASE_ADDRESS     0x41800000
	#define POOL_BUFFER_ADDRESS   0x41900000

	/* Memory */
	#define PROGRAM_STACK_RAM_ADDRESS  0x00000000
	#define GLOBAL_BUFFER_ADDRESS      0x44000000
	#define SHARED_MEM_ADDRESS         0x50000000

/*  Hardware parameters
 *     width and size are specified in bytes
 *     quantum and period are specified in SC_NS
 */
	/* OVP platform quantum*/
	#define PLAT_QUANTUM 1

	/* Bus width */
	#define BUS_WIDTH 4

	/* Register Set */
	#define STATUS_REG         single_reg_set[0]
	// #define GROUP_0_STATUS_REG single_reg_set[0](15, 0)
	// #define GROUP_1_STATUS_REG single_reg_set[0](31, 16)
	#define CONFIG_READY_REG   single_reg_set[1][0]
	#define CONFIG_GROUP_REG   single_reg_set[2][0]
	#define SOURCE_GROUP_REG   single_reg_set[2][1]
	#define GROUP_0_OP_ENABLE  double_reg_set_0[0][0]
	#define GROUP_1_OP_ENABLE  double_reg_set_1[0][0]

	/* Convolution Core */
	#define CONV_SINGLE_REG_NUM 5
	#define CONV_DOUBLE_REG_NUM 18
	#define PE_ARRAY_HEIGHT     12
	#define PE_ARRAY_WIDTH      14
	#define CONV_PERIOD         1
	#define CONV_BUFFER_SIZE    0x100000

	/* Activation Engine */
	#define ACT_SINGLE_REG_NUM 3
	#define ACT_DOUBLE_REG_NUM 11
	#define ACT_THROUGHPUT     1
	#define ACT_PERIOD         1
	#define ACT_BUFFER_SIZE    0x100000

	/* Pooing Engine */
	#define POOL_SINGLE_REG_NUM 3
	#define POOL_DOUBLE_REG_NUM 14
	#define POOL_PERIOD         1
	#define POOL_BUFFER_SIZE    0x100000

	/* DMA */
	#define DMA_CHANNEL_NUM 16
	#define DMA_PERIOD      1

	/* Memory */
	#define PROGRAM_STACK_RAM_SIZE 0x20000000

	#define GLOBAL_BUFFER_SIZE          0x4000000
	#define GLOBAL_BUFFER_READ_LATENCY  3
	#define GLOBAL_BUFFER_WRITE_LATENCY 2

	#define SHARED_MEM_SIZE          0x30000000
	#define SHARED_MEM_READ_LATENCY  30
	#define SHARED_MEM_WRITE_LATENCY 20

#endif /*CONFIG_H*/
