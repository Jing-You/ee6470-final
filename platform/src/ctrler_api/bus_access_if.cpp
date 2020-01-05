#include "bus_access_if.h"

#ifdef USING_TLM_SOCKET
	BusAccessIF::BusAccessIF(scml2::initiator_socket<32> &local_i_socket,
	                         scml2::initiator_socket<32> &global_i_socket)
	:
		mLocalISocket(local_i_socket),
		mGlobalISocket(global_i_socket),
		dram_start_address(SHARED_MEM_ADDRESS),
		dram_end_address(static_cast<unsigned long long>(SHARED_MEM_ADDRESS) + SHARED_MEM_SIZE - 1)
	{}

	void BusAccessIF::write_reg(uint address, const uint data) {
		mLocalISocket.write<uint>(address, data);
	}

	uint BusAccessIF::read_reg(uint address) {
		uint data(0);
		mLocalISocket.read<uint>(address, data);
		return data;
	}

	void BusAccessIF::write_data(unsigned long long address, unsigned char* data, uint size) {
		if((address >= dram_start_address) && (address <= dram_end_address))
			mGlobalISocket.write_debug<unsigned char>(address, data, size);
		else
			mLocalISocket.write_debug<unsigned char>(address, data, size);
	}

	void BusAccessIF::read_data(unsigned long long address, unsigned char* data, uint size) {
		if((address >= dram_start_address) && (address <= dram_end_address))
			mGlobalISocket.read_debug<unsigned char>(address, data, size);
		else
			mLocalISocket.read_debug<unsigned char>(address, data, size);
	}

#else
	BusAccessIF::BusAccessIF() {}

	void BusAccessIF::write_reg(uint address, const uint data) {
		*reinterpret_cast<volatile uint*>(address) = data;
	}

	uint BusAccessIF::read_reg(uint address) {
		auto data = *reinterpret_cast<volatile uint*>(address);

		return data;
	}

	void BusAccessIF::write_data(unsigned long long address, unsigned char* data, uint size) {
		memcpy(reinterpret_cast<void*>(address), data, size);
	}
	
	void BusAccessIF::read_data(unsigned long long address, unsigned char* data, uint size) {
		memcpy(data, reinterpret_cast<void*>(address), size);
	}
#endif
