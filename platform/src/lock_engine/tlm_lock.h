#ifndef tlm_lock_H
#define tlm_lock_H

#include <iostream>

class tlm_lock {
  public:

    uint32_t readm(uint32_t &d) {
      if (d != 0x0)
        return 0x1;
  
      else
        return d;
    }

    void wr_transport(uint magic_address, uint data) {
#ifdef DEBUG
      std::cout << "wr address: " << std::hex << magic_address << ", data: " << data << std::endl;
  
#endif
      uint32_t addr = magic_address;
      uint32_t command = magic_address == 0x20987 ? 1 : 0;
  
      unsigned int resp;
  
      switch (command) {
        case 1: // Packet is a READ one
          if (readm(value) != 0)
            resp = 1;
          else
            resp = 0;
   
          data = resp;
   
          value = 0x1;
   
        case 0: // Packet is a WRITE
          if (data == 0)
            value = 0;
          else
            value = 1;
          break;
      }
    }


    int rd_transport(uint magic_address, uint data) {
  
      uint32_t addr = magic_address;
      uint32_t command = magic_address == 0x20987 ? 1 : 0;
  
      unsigned int resp;
  
      switch (command) {
        case 1: // Packet is a READ one
          if (readm(value) != 0)
            resp = 1;
          else
            resp = 0;
   
          //data = resp;
   
          value = 0x1;

#ifdef DEBUG
          std::cout << "rd address: " << std::hex << magic_address << ", data: " << resp << std::endl;
#endif

          return resp;
   
        case 0: // Packet is a WRITE
          if (data == 0)
            value = 0;
          else
            value = 1;
          break;
      }
    }

    tlm_lock() { value = 0;}
    ~tlm_lock() {}

  private:
    uint32_t value;
};


#endif // tlm_lock_H_
