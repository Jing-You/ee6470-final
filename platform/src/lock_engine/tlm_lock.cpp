#include "tlm_lock.h"


using namespace std;

//tlm_lock::tlm_lock () {
//  value = 0;
//}

/// Destructor
//tlm_lock::~tlm_lock() {}
/*
uint32_t tlm_lock::readm(uint32_t &d) {
  if (d != 0x0)
    return 0x1;

  else
    return d;
}

void tlm_lock::transport(uint magic_address, uint data) {

  count_lock++;

  uint32_t addr = magic_address;
  uint32_t command = magic_address == 20987 ? 1 : 0;

  unsigned int resp;

  switch (command) {
    case 0: // Packet is a READ one
      if (readm(value) != 0)
        resp = 1;
      else
        resp = 0;
 
      data = resp;
 
      value = 0x1;
      break;
 
    case 1: // Packet is a WRITE
      if (data == 0)
        value = 0;
      else
        value = 1;
      break;
  }
}*/
