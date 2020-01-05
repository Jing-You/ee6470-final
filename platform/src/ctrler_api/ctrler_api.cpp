#include "ctrler_api/ctrler_api.h"

#ifdef USING_TLM_SOCKET
	ControllerAPI::ControllerAPI(scml2::initiator_socket<32> &local_i_socket,
	                             scml2::initiator_socket<32> &global_i_socket)
	:
		bus_access_if(local_i_socket, global_i_socket)
	{}
#else
	ControllerAPI::ControllerAPI() {}
#endif

uint ControllerAPI::ReadStatus(eSubUnit engine_or_dma)
{
	unsigned long long status_address(0);

	switch(engine_or_dma) {
	case is_bridge_dma:
		status_address = BRIDGE_DMA_BASE_ADDRESS;
		break;
	case is_conv_dma:
		status_address = CONV_DMA_BASE_ADDRESS;
		break;
	case is_act_dma_0:
		status_address = ACT_DMA_0_BASE_ADDRESS;
		break;
	case is_act_dma_1:
		status_address = ACT_DMA_1_BASE_ADDRESS;
		break;
	case is_pool_dma:
		status_address = POOL_DMA_BASE_ADDRESS;
		break;
	case is_conv_core:
		status_address = CONV_BASE_ADDRESS;
		break;
	case is_act_engine_0:
		status_address = ACT_0_BASE_ADDRESS;
		break;
	case is_act_engine_1:
		status_address = ACT_1_BASE_ADDRESS;
		break;
	case is_pool_engine:
		status_address = POOL_BASE_ADDRESS;
		break;
	default: assert(0 && "Error in specifying sub-uint.");
	}

#ifdef USING_TLM_SOCKET
	wait(1, SC_NS);
#endif

	auto status(bus_access_if.read_reg(status_address));

#ifdef USING_TLM_SOCKET
	wait(1, SC_NS);
#endif

	return status;
}

bool ControllerAPI::ReadConfigReady(eSubUnit engine)
{
	bool is_config_ready(false);
	unsigned long long config_ready_address(0);

	switch(engine) {
	case is_conv_core:
		config_ready_address = CONV_BASE_ADDRESS + 0x4;
		break;
	case is_act_engine_0:
		config_ready_address = ACT_0_BASE_ADDRESS + 0x4;
		break;
	case is_act_engine_1:
		config_ready_address = ACT_1_BASE_ADDRESS + 0x4;
		break;
	case is_pool_engine:
		config_ready_address = POOL_BASE_ADDRESS + 0x4;
		break;
	default: assert(0 && "Error in specifying sub-uint.");
	}

#ifdef USING_TLM_SOCKET
	wait(1, SC_NS);
#endif

	auto config_ready(bus_access_if.read_reg(config_ready_address));

#ifdef USING_TLM_SOCKET
	wait(1, SC_NS);
#endif

	if(config_ready != 0)
		is_config_ready = true;
	
	return is_config_ready;
}

void ControllerAPI::ConfigConvCore(uint feature_in_address, uint filter_in_address,
                                   uint feature_out_address,
                                   shape_t &input_shape, shape_t &kernel_shape,
                                   shape_t &output_shape, uint stride,
                                   eDataType HWDtype, eConvMode mode,
                                   EyerissMappingParamter &hint)
{
#ifdef USING_TLM_SOCKET
	wait(16, SC_NS);
#endif

	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM +  1) << 2 ), static_cast<uint>(mode));
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM +  2) << 2 ), static_cast<uint>(HWDtype));
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM +  3) << 2 ), feature_in_address);
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM +  4) << 2 ), filter_in_address);
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM +  5) << 2 ), feature_out_address);
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM +  6) << 2 ), (input_shape.w << 16) + (input_shape.h & 0xFFFF));
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM +  7) << 2 ), input_shape.c);
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM +  8) << 2 ), input_shape.n);
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM +  9) << 2 ), (kernel_shape.w << 16) + (kernel_shape.h & 0xFFFF));
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM + 10) << 2 ), (kernel_shape.n << 16) + (kernel_shape.c & 0xFFFF));
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM + 11) << 2 ), (output_shape.w << 16) + (output_shape.h & 0xFFFF));
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM + 12) << 2 ), kernel_shape.n);
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM + 13) << 2 ), stride);
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM + 14) << 2 ), 0);
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM + 15) << 2 ), hint.EncodeParameter());
	bus_access_if.write_reg(CONV_BASE_ADDRESS + ((CONV_SINGLE_REG_NUM + 16) << 2 ), 0);
}

void ControllerAPI::ProgramPoolReg(ePoolFunction pool_function, eDataType HWDtype,
                                   uint data_in_address, uint data_out_address,
                                   uint data_in_channel, uint data_in_height, uint data_in_width,
                                   uint data_out_channel, uint data_out_height, uint data_out_width,
                                   uint filter_width, uint filter_stride, uint zero_padding)
{
#ifdef USING_TLM_SOCKET
	wait(13, SC_NS);
#endif

	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM +  1) << 2), static_cast<uint>(pool_function));
	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM +  2) << 2), static_cast<uint>(HWDtype));
	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM +  3) << 2), data_in_address);
	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM +  4) << 2), data_out_address);
	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM +  5) << 2), data_in_width);
	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM +  6) << 2), data_in_height);
	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM +  7) << 2), data_in_channel);
	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM +  8) << 2), data_out_width);
	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM +  9) << 2), data_out_height);
	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM + 10) << 2), data_out_channel);
	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM + 11) << 2), filter_width);
	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM + 12) << 2), filter_stride);
	bus_access_if.write_reg(POOL_BASE_ADDRESS + ((POOL_SINGLE_REG_NUM + 13) << 2), zero_padding);
}

void ControllerAPI::ProgramActReg(eSubUnit act_engine, eActFunction act_function, eDataType HWDtype,
                                  uint data_in_address, uint data_out_address,
                                  uint data_channel, uint data_height, uint data_width)
{
	uint act_base_address(0);
	uint act_buffer_address(0);
	switch(act_engine) {
	case is_act_engine_0:
		act_base_address   = ACT_0_BASE_ADDRESS;
		act_buffer_address = ACT_BUFFER_0_ADDRESS;
		break;
	case is_act_engine_1:
		act_base_address   = ACT_1_BASE_ADDRESS;
		act_buffer_address = ACT_BUFFER_1_ADDRESS;
		break;
	default: assert(0 && "Error in specifying sub-uint.");
	}

#ifdef USING_TLM_SOCKET
	wait(10, SC_NS);
#endif

	bus_access_if.write_reg(act_base_address + ((ACT_SINGLE_REG_NUM +  1) << 2), static_cast<uint>(act_function));
	bus_access_if.write_reg(act_base_address + ((ACT_SINGLE_REG_NUM +  2) << 2), static_cast<uint>(HWDtype));
	bus_access_if.write_reg(act_base_address + ((ACT_SINGLE_REG_NUM +  3) << 2), data_in_address);
	bus_access_if.write_reg(act_base_address + ((ACT_SINGLE_REG_NUM +  4) << 2), data_out_address);
	bus_access_if.write_reg(act_base_address + ((ACT_SINGLE_REG_NUM +  5) << 2), data_width);
	bus_access_if.write_reg(act_base_address + ((ACT_SINGLE_REG_NUM +  6) << 2), data_height);
	bus_access_if.write_reg(act_base_address + ((ACT_SINGLE_REG_NUM +  7) << 2), data_channel);
	bus_access_if.write_reg(act_base_address + ((ACT_SINGLE_REG_NUM +  8) << 2), 0);
	bus_access_if.write_reg(act_base_address + ((ACT_SINGLE_REG_NUM +  9) << 2), act_buffer_address + 0x50000);
	bus_access_if.write_reg(act_base_address + ((ACT_SINGLE_REG_NUM + 10) << 2), act_buffer_address + 0x60000);
}

void ControllerAPI::ConfigDMA(eSubUnit dma, vector<ChannelConfig> &ch_config)
{
	assert(!ch_config.empty() && "Config channels number shouldn't be zero.");
	assert((ch_config.size() <= DMA_CHANNEL_NUM)
	       && "Config channels number shouldn't be bigger than DMA supported channels number");
	
	unsigned long long dma_base_address(0);
	switch(dma) {
	case is_bridge_dma:
		dma_base_address = BRIDGE_DMA_BASE_ADDRESS;
		break;
	case is_conv_dma:
		dma_base_address = CONV_DMA_BASE_ADDRESS;
		break;
	case is_act_dma_0:
		dma_base_address = ACT_DMA_0_BASE_ADDRESS;
		break;
	case is_act_dma_1:
		dma_base_address = ACT_DMA_1_BASE_ADDRESS;
		break;
	case is_pool_dma:
		dma_base_address = POOL_DMA_BASE_ADDRESS;
		break;
	default: assert(0 && "Error in specifying sub-uint.");
	}

	for(uint i = 0; i < ch_config.size(); i++) {
		if(ch_config[i].channel_enable == 1) {
			#ifdef USING_TLM_SOCKET
				wait(7, SC_NS);
			#endif

			bus_access_if.write_reg(dma_base_address + ((16 * (i + 1) + 1) << 2), ch_config[i].source_address);
			bus_access_if.write_reg(dma_base_address + ((16 * (i + 1) + 2) << 2), ch_config[i].dest_address);
			bus_access_if.write_reg(dma_base_address + ((16 * (i + 1) + 3) << 2), ch_config[i].transfer_length);
			bus_access_if.write_reg(dma_base_address + ((16 * (i + 1) + 4) << 2), ch_config[i].transfer_type);
			bus_access_if.write_reg(dma_base_address + ((16 * (i + 1) + 5) << 2), ch_config[i].line_length);
			bus_access_if.write_reg(dma_base_address + ((16 * (i + 1) + 6) << 2), ch_config[i].line_stride);
			bus_access_if.write_reg(dma_base_address + ((16 * (i + 1) + 0) << 2), ch_config[i].channel_enable);
		}
	}
}

void ControllerAPI::SetOPEnable(eSubUnit engine_or_dma)
{
	unsigned long long op_enable_address(0);

	switch(engine_or_dma) {
	case is_bridge_dma:
		op_enable_address = BRIDGE_DMA_BASE_ADDRESS + (1 << 2);
		break;
	case is_conv_dma:
		op_enable_address = CONV_DMA_BASE_ADDRESS + (1 << 2);
		break;
	case is_act_dma_0:
		op_enable_address = ACT_DMA_0_BASE_ADDRESS + (1 << 2);
		break;
	case is_act_dma_1:
		op_enable_address = ACT_DMA_1_BASE_ADDRESS + (1 << 2);
		break;
	case is_pool_dma:
		op_enable_address = POOL_DMA_BASE_ADDRESS + (1 << 2);
		break;
	case is_conv_core:
		op_enable_address = CONV_BASE_ADDRESS + (CONV_SINGLE_REG_NUM << 2);
		break;
	case is_act_engine_0:
		op_enable_address = ACT_0_BASE_ADDRESS + (ACT_SINGLE_REG_NUM << 2);
		break;
	case is_act_engine_1:
		op_enable_address = ACT_1_BASE_ADDRESS + (ACT_SINGLE_REG_NUM << 2);
		break;
	case is_pool_engine:
		op_enable_address = POOL_BASE_ADDRESS + (POOL_SINGLE_REG_NUM << 2);
		break;
	default: assert(0 && "Error in specifying sub-uint.");
	}

#ifdef USING_TLM_SOCKET
	wait(1, SC_NS);
#endif

	bus_access_if.write_reg(op_enable_address, 1);
}

void ControllerAPI::ClearDMAOPEnable(eSubUnit dma)
{
	unsigned long long op_enable_address(0);

	switch(dma) {
	case is_bridge_dma:
		op_enable_address = BRIDGE_DMA_BASE_ADDRESS + (1 << 2);
		break;
	case is_conv_dma:
		op_enable_address = CONV_DMA_BASE_ADDRESS + (1 << 2);
		break;
	case is_act_dma_0:
		op_enable_address = ACT_DMA_0_BASE_ADDRESS + (1 << 2);
		break;
	case is_act_dma_1:
		op_enable_address = ACT_DMA_1_BASE_ADDRESS + (1 << 2);
		break;
	case is_pool_dma:
		op_enable_address = POOL_DMA_BASE_ADDRESS + (1 << 2);
		break;
	default: assert(0 && "Error in specifying sub-uint.");
	}

#ifdef USING_TLM_SOCKET
	wait(1, SC_NS);
#endif

	bus_access_if.write_reg(op_enable_address, 0);
}

bool ControllerAPI::CheckCbufRefreshReady() {
	#ifdef USING_TLM_SOCKET
		wait(1, SC_NS);
	#endif

		auto cbuf_ready(bus_access_if.read_reg(CONV_BASE_ADDRESS + (3 << 2)));

	#ifdef USING_TLM_SOCKET
		wait(1, SC_NS);
	#endif

	return (cbuf_ready ? true : false);
}

void ControllerAPI::SetCbufRefreshValid() {
#ifdef USING_TLM_SOCKET
	wait(1, SC_NS);
#endif

	bus_access_if.write_reg(CONV_BASE_ADDRESS + (4 << 2), 1);
}

void ControllerAPI::ClearCbufRefreshValid() {
#ifdef USING_TLM_SOCKET
	wait(1, SC_NS);
#endif

	bus_access_if.write_reg(CONV_BASE_ADDRESS + (4 << 2), 0);
}

void ControllerAPI::DebugWriteData(unsigned long long address,
                                   unsigned char* data,
                                   uint size)
{
	bus_access_if.write_data(address, data, size);
}

void ControllerAPI::DebugReadData(unsigned long long address,
                                  unsigned char* data,
                                  uint size)
{
	bus_access_if.read_data(address, data, size);
}
