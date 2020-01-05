/*****************************************************************************

	The following code is derived, directly or indirectly, from the SystemC
	source code Copyright (c) 1996-2008 by all Contributors.
	All Rights reserved.

	The contents of this file are subject to the restrictions and limitations
	set forth in the SystemC Open Source License Version 3.0 (the "License");
	You may not use this file except in compliance with such restrictions and
	limitations. You may obtain instructions on how to receive a copy of the
	License at http://www.systemc.org/. Software distributed by Contributors
	under the License is distributed on an "AS IS" basis, WITHOUT WARRANTY OF
	ANY KIND, either express or implied. See the License for the specific
	language governing rights and limitations under the License.

 *****************************************************************************/

/*****************************************************************************


 *****************************************************************************/

#ifndef SIMPLEBUSLT_H__
#define SIMPLEBUSLT_H__

#include "tlm"

#include "tlm_utils/simple_target_socket.h"
#include "tlm_utils/simple_initiator_socket.h"

#include "simple_address_map.h"

/* 2018/08/08 Chun-Tse: There is a #define "delay" in ArchC RISC-V source code */
#undef delay

template <int NR_OF_TARGET_SOCKETS, int NR_OF_INITIATOR_SOCKETS>
class SimpleBus : public sc_core::sc_module
{
	public:
		typedef tlm::tlm_generic_payload                 transaction_type;
		typedef tlm::tlm_phase                           phase_type;
		typedef tlm::tlm_sync_enum                       sync_enum_type;
		typedef tlm_utils::simple_target_socket_tagged<SimpleBus>    target_socket_type;
		typedef tlm_utils::simple_initiator_socket_tagged<SimpleBus> initiator_socket_type;

	public:
		//2013-10-13 14:37:39, tshsu: NR_OF_INITIATOR_SOCKETS means #. of "target" module == #. of "initiator" sockets of bus.
		target_socket_type target_socket[NR_OF_TARGET_SOCKETS];
		initiator_socket_type initiator_socket[NR_OF_INITIATOR_SOCKETS];

	public:
		SC_HAS_PROCESS(SimpleBus);
		SimpleBus(sc_core::sc_module_name name, double clock_period_in_ps = 1000 ) :
			sc_core::sc_module(name), 
			m_masks( NR_OF_INITIATOR_SOCKETS, 0xffffffffffffffffULL ),
			m_target_count(0),
			clock_period( clock_period_in_ps, sc_core::SC_PS )
	{
		for (unsigned int i = 0; i < NR_OF_TARGET_SOCKETS; ++i) {
			target_socket[i].register_b_transport(this, &SimpleBus::initiatorBTransport, i);
			target_socket[i].register_transport_dbg(this, &SimpleBus::transportDebug, i);
			target_socket[i].register_get_direct_mem_ptr(this, &SimpleBus::getDMIPointer, i);
		}
		for (unsigned int i = 0; i < NR_OF_INITIATOR_SOCKETS; ++i) {
			initiator_socket[i].register_invalidate_direct_mem_ptr(this, &SimpleBus::invalidateDMIPointers, i);
		}

	}
		void bindTargetSocket(typename initiator_socket_type::base_target_socket_type& target
				,sc_dt::uint64 low
				,sc_dt::uint64 high
				,sc_dt::uint64 mask = 0xffffffffffffffffULL){
			initiator_socket[m_target_count](target); //bind sockets
			//insert into address map and increase target count
			// (we have to count the targets manually, because target_socket.size() is only reliable during simulation
			//  as it gets evaluated during end_of_elaboration)
			setMemoryMap( m_target_count++, low, high, mask );
		}
		/*
		*/

		void setMemoryMap(unsigned int target_id
				,sc_dt::uint64 low
				,sc_dt::uint64 high
				,sc_dt::uint64 mask = 0xffffffffffffffffULL){
			assert( target_id < NR_OF_INITIATOR_SOCKETS );
			//insert into address map and increase target count
			// (we have to count the targets manually, because target_socket.size() is only reliable during simulation
			//  as it gets evaluated during end_of_elaboration)
			m_addrMap.insert(low, high, target_id);
			m_masks[target_id] = mask; //add the mask for this target
		}

		sc_dt::uint64 getAddressOffset(unsigned int initiator_socket_id)
		{
			return m_addrMap.getBaseAddress( initiator_socket_id );
		}

		sc_dt::uint64 getAddressMask(unsigned int initiator_socket_id)
		{
			return m_masks[initiator_socket_id];
		}

		unsigned int decode(const sc_dt::uint64& address)
		{
			return m_addrMap.decode(address);
		}

		void set_clock_period( sc_core::sc_time t )
		{
			clock_period = t;
		}
		sc_core::sc_time get_clock_period()
		{
			return clock_period;
		}

		sc_core::sc_time delay( transaction_type& trans )
		{
			//Note that 4 means bus width is 4 bytes; not good enough coding.
			return (1 +  trans.get_data_length() / 4 )*clock_period;
		}

		//
		// interface methods
		//

		//
		// Lt protocol
		// - forward each call to the target/initiator
		//
		void initiatorBTransport(int SocketId,
				transaction_type& trans,
				sc_core::sc_time& t)
		{
			initiator_socket_type* decodeSocket;
			unsigned int initiator_socket_id = decode(trans.get_address());
			assert(initiator_socket_id < NR_OF_INITIATOR_SOCKETS);
			decodeSocket = &initiator_socket[initiator_socket_id];
			trans.set_address(trans.get_address() & getAddressMask(initiator_socket_id));

			t += delay( trans );

			(*decodeSocket)->b_transport(trans, t);
		}

		unsigned int transportDebug(int SocketId,
				transaction_type& trans)
		{
			unsigned int initiator_socket_id = decode(trans.get_address());
			assert(initiator_socket_id < NR_OF_INITIATOR_SOCKETS);
			initiator_socket_type* decodeSocket = &initiator_socket[initiator_socket_id];
			trans.set_address( trans.get_address() & getAddressMask(initiator_socket_id) );

			return (*decodeSocket)->transport_dbg(trans);
		}

		bool limitRange(unsigned int initiator_socket_id, sc_dt::uint64& low, sc_dt::uint64& high)
		{
			sc_dt::uint64 addressOffset = getAddressOffset(initiator_socket_id);
			sc_dt::uint64 addressMask = getAddressMask(initiator_socket_id);

			if (low > addressMask) {
				// Range does not overlap with addressrange for this target
				return false;
			}

			low += addressOffset;
			if (high > addressMask) {
				high = addressOffset + addressMask;

			} else {
				high += addressOffset;
			}
			return true;
		}

		bool getDMIPointer(int SocketId,
				transaction_type& trans,
				tlm::tlm_dmi&  dmi_data)
		{
			sc_dt::uint64 address = trans.get_address();

			unsigned int initiator_socket_id = decode(address);
			assert(initiator_socket_id < NR_OF_INITIATOR_SOCKETS);
			initiator_socket_type* decodeSocket = &initiator_socket[initiator_socket_id];
			sc_dt::uint64 maskedAddress = address & getAddressMask(initiator_socket_id);

			trans.set_address(maskedAddress);

			bool result =
				(*decodeSocket)->get_direct_mem_ptr(trans, dmi_data);

			if (result)
			{
				// Range must contain address
				assert(dmi_data.get_start_address() <= maskedAddress);
				assert(dmi_data.get_end_address() >= maskedAddress);
			}

			// Should always succeed
			sc_dt::uint64 start, end;
			start = dmi_data.get_start_address();
			end = dmi_data.get_end_address();

			limitRange(initiator_socket_id, start, end);

			dmi_data.set_start_address(start);
			dmi_data.set_end_address(end);

			return result;
		}

		void invalidateDMIPointers(int port_id,
				sc_dt::uint64 start_range,
				sc_dt::uint64 end_range)
		{
			// FIXME: probably faster to always invalidate everything?

			if (!limitRange(port_id, start_range, end_range)) {
				// Range does not fall into address range of target
				return;
			}

			for (unsigned int i = 0; i < NR_OF_TARGET_SOCKETS; ++i) {
				(target_socket[i])->invalidate_direct_mem_ptr(start_range, end_range);
			}
		}

	private:
		SimpleAddressMap m_addrMap; //a pretty simple address map
		std::vector<sc_dt::uint64> m_masks; //address masks for each target
		unsigned int m_target_count;  //number of connected targets (see bindTargetSocket for explanation)
		sc_core::sc_time clock_period;

};

#endif
