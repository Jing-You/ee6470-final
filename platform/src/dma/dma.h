#ifndef DMA_H
#define DMA_H

#include <scml2.h>
#include <systemc>
#include "common/config.h"

class DMA : public sc_module {
public:
	/* Port list */
	scml2::initiator_socket<32> global_i_socket;
	scml2::initiator_socket<32> local_i_socket;

	/* Config bus view */
	scml2::memory<uint> config_reg;

	/* Constructor */
	SC_HAS_PROCESS(DMA);
	DMA(const sc_module_name &name,
		 eDMAType type,
	    unsigned long long local_start_address,
	    unsigned long long local_end_address);

	/* Destructor */
	~DMA();

public:
	/* Methods */
	void PrintConfigReg() const;

private:
	/* Main thread */
	void DMAThread0();
	void DMAThread1();
	void DMAThread2();
	void DMAThread3();
	void DMAThread4();
	void DMAThread5();
	void DMAThread6();
	void DMAThread7();
	void DMAThread8();
	void DMAThread9();
	void DMAThread10();
	void DMAThread11();
	void DMAThread12();
	void DMAThread13();
	void DMAThread14();
	void DMAThread15();

	/* Methods */
	void DoDMA(int ch_index);
	void ChannelThread(int ch_index);

	/* Write callback methods for event driven config register */
	bool WriteMode(const uint &dma_mode);

private:
	/* Config bus view aliases */
	scml2::reg<uint> status;
	scml2::reg<uint> mode;
	
	scml2::reg<uint>* channel_enable [DMA_CHANNEL_NUM];
	scml2::reg<uint>* source_address [DMA_CHANNEL_NUM];
	scml2::reg<uint>* dest_address   [DMA_CHANNEL_NUM];
	scml2::reg<uint>* transfer_length[DMA_CHANNEL_NUM];
	scml2::reg<uint>* transfer_type  [DMA_CHANNEL_NUM];
	scml2::reg<uint>* line_length    [DMA_CHANNEL_NUM];
	scml2::reg<uint>* line_stride    [DMA_CHANNEL_NUM];

	sc_event event_dma_start;

	const eDMAType type;
	const unsigned long long local_start_address;
	const unsigned long long local_end_address;

	const sc_time dma_period;
};

#endif /*DMA_H*/
