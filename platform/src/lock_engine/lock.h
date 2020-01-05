#ifndef Lock_engine_H
#define Lock_engine_H

#include <scml2.h>
#include <systemc>
#include "common/config.h"
#include "lock_engine/tlm_lock.h"

class Lock_engine : public sc_module {
public:
	/* Port list */
	scml2::initiator_socket<32> global_i_socket;
	scml2::initiator_socket<32> local_i_socket;

	/* Config bus view */
	scml2::memory<uint> config_reg;

	/* Constructor */
	SC_HAS_PROCESS(Lock_engine);
	Lock_engine(const sc_module_name &name,
		 eLOCKType type,
	    unsigned long long local_start_address,
	    unsigned long long local_end_address);

	/* Destructor */
	~Lock_engine();
private:
        uint32_t readm(uint32_t &d);

	/* Write callback methods for event driven config register */
	bool ReadMode(uint &lock_mode);
	bool WriteMode(const uint &lock_mode);
private:
        uint32_t value;
	/* Config bus view aliases */
	scml2::reg<uint> lock;

};

#endif
