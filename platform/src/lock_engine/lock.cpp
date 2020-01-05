#include "lock.h"

Lock_engine::Lock_engine(const sc_module_name &name,
         eLOCKType type,
         unsigned long long local_start_address,
         unsigned long long local_end_address) :
	sc_module(name),
	global_i_socket("global_i_socket"),
	local_i_socket("local_i_socket"),
	config_reg("config_reg", 2*16),
	lock("lock", config_reg,  0)
{
        value = 0;
	/* Initialization */
	config_reg.initialize(0);

	/* Callback registrations */
	set_word_read_callback(lock, SCML2_CALLBACK(ReadMode), scml2::NEVER_SYNCING);
	set_word_write_callback(lock, SCML2_CALLBACK(WriteMode), scml2::NEVER_SYNCING);

	cout << this->name() << " has been instantiated.\n"
	     << "[Information]\n"
	     << "           Local address space: 0x" << hex << local_start_address << " ~ 0x" << local_end_address << dec << '\n'
             << endl;

}

Lock_engine::~Lock_engine() {
}

uint32_t Lock_engine::readm(uint32_t &d) {
  if (d != 0x0)
    return 0x1;
  else
    return d;
}


bool Lock_engine::ReadMode(uint &lock_mode) {

  unsigned int resp;

  if(readm(value) != 0)
    resp = 1;
  else
    resp = 0;

  //*((uint32_t *)data_pointer) = resp;
  lock_mode = resp;
  //cout << "read mode, lock: " << lock_mode << endl;

  value = 0x1;

  return true;
  
}

bool Lock_engine::WriteMode(const uint &lock_mode) {
  //cout << "write mode, lock: " << lock_mode << endl;

  //if(*((uint32_t *)data_pointer) == 0)
  if(lock_mode == 0)
    value = 0;
  else
    value = 1;

  return true;
  
}
