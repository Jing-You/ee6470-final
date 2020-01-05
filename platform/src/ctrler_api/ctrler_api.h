#pragma once

#ifdef USING_TLM_SOCKET
	#include <scml2.h>
	#include <systemc>
#endif

#include <vector>
#include "bus_access_if.h"
#include "common/config.h"
#include "common/utility_class.h"

/* DMA channel config resgisters */
struct ChannelConfig {
	uint channel_enable;
	uint source_address;
	uint dest_address;
	uint transfer_length;
	uint transfer_type;
	uint line_length;
	uint line_stride;
};

typedef struct ChannelConfig ChannelConfig;

class ControllerAPI {
public:
	/* Constructor */
	#ifdef USING_TLM_SOCKET
		ControllerAPI(scml2::initiator_socket<32> &local_i_socket,
		              scml2::initiator_socket<32> &global_i_socket);
	#else
		ControllerAPI();
	#endif

public:
	/* Methods */
	uint
	ReadStatus
	(eSubUnit engine_or_dma);

	bool
	ReadConfigReady
	(eSubUnit engine);

	void
	ConfigConvCore
	(uint feature_in_address, uint filter_in_address,
	 uint feature_out_address,
	 shape_t &input_shape, shape_t &kernel_shape,
	 shape_t &output_shape, uint stride,
	 eDataType HWDtype, eConvMode mode,
	 EyerissMappingParamter &hint);

	void
	ProgramPoolReg
	(ePoolFunction pool_function, eDataType HWDtype,
	 uint data_in_address, uint data_out_address,
	 uint data_in_channel, uint data_in_height, uint data_in_width,
	 uint data_out_channel, uint data_out_height, uint data_out_width,
	 uint filter_width, uint filter_stride, uint zero_padding);

	void
	ProgramActReg
	(eSubUnit act_engine, eActFunction act_function, eDataType HWDtype,
	 uint data_in_address, uint data_out_address,
	 uint data_channel, uint data_height, uint data_width);

	void
	ConfigDMA
	(eSubUnit dma, vector<ChannelConfig> &ch_config);

	void
	SetOPEnable
	(eSubUnit engine_or_dma);

	void
	ClearDMAOPEnable
	(eSubUnit dma);

	bool
	CheckCbufRefreshReady
	();

	void
	SetCbufRefreshValid
	();

	void
	ClearCbufRefreshValid
	();

	/* The following "address" and "size" are specified in bytes. */
	void
	DebugWriteData
	(unsigned long long address,
	 unsigned char* data,
	 uint size);

	void
	DebugReadData
	(unsigned long long address,
	 unsigned char* data,
	 uint size);

private:
	BusAccessIF bus_access_if;
};