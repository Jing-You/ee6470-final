#ifdef USING_TLM_SOCKET
	#include <scml2.h>
	#include <systemc>
	#include "common/config.h"
#else
	#include <cstring>
#endif

typedef unsigned int uint;

class BusAccessIF {
public:
	#ifdef USING_TLM_SOCKET
		BusAccessIF(scml2::initiator_socket<32> &local_i_socket,
		            scml2::initiator_socket<32> &global_i_socket);
	#else
		BusAccessIF();
	#endif

/*  The address and size are specified in bytes */
public:
	/* Access register methods */
	void write_reg(uint address, const uint data);
	uint read_reg(uint address);

	/* Access data methods */
	void write_data(unsigned long long address, unsigned char* data, uint size);
	void read_data(unsigned long long address, unsigned char* data, uint size);

#ifdef USING_TLM_SOCKET
	private:
		scml2::initiator_socket<32> &mLocalISocket;
		scml2::initiator_socket<32> &mGlobalISocket;
		unsigned long long dram_start_address;
		unsigned long long dram_end_address;
#endif
};
