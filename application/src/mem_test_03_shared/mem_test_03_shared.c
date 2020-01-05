#include <stdio.h>
#include <assert.h>
#include "../utility/acPthread.h"

#define REG_S32 *(volatile  int*)

int get_id();

// global variables in shared memory
volatile mutex_t *mutex = (volatile mutex_t *)0x52ff0000; // 4-byte: 0x52ff0000 - 0x52ff0003
volatile barrier_t *barr      = (volatile barrier_t *)0x52ff0004; // 16-byte: 0x52ff0004 - 0x52ff0013

static const unsigned int shared_mem_start = 0x50000000u;
static const unsigned int shared_mem_per_core_size  = 0x00400000u;

void mem_test() {
        int PROCESSORS = 4;
        barrier_init(barr,PROCESSORS);

	unsigned int start = 0;
	
	if (get_id() == 0) { printf("========== Phase 1 ==========\n"); }
	start = shared_mem_start + shared_mem_per_core_size*get_id();
	printf("Core %d: start == %p\n", get_id(), start);
	for (unsigned int addr = start; addr < start+shared_mem_per_core_size; addr+=4) {
		*(unsigned int*)(addr) = addr;
		if (*(unsigned int*)(addr) != addr) {
			printf("Core %d: mem[%p] == %p != %p\n", get_id(), addr, (*(unsigned int*)(addr)), addr);
		}
	}

        barrier(barr);
		
	if (get_id() == 0) { printf("========== Phase 2 ==========\n"); }
	start = shared_mem_start + shared_mem_per_core_size*((get_id()+1)%3);
	printf("Core %d: start == %p\n", get_id(), start);
	for (unsigned int addr = start; addr < start+shared_mem_per_core_size; addr+=4) {
		*(unsigned int*)(addr) = addr;
		if (*(unsigned int*)(addr) != addr) {
			printf("Core %d: mem[%p] == %p != %p\n", get_id(), addr, (*(unsigned int*)(addr)), addr);
		}
	}
	
        barrier(barr);

	if (get_id() == 0) { printf("========== Phase 3 ==========\n"); }
	start = shared_mem_start + shared_mem_per_core_size*((get_id()+2)%3);
	printf("Core %d: start == %p\n", get_id(), start);
	for (unsigned int addr = start; addr < start+shared_mem_per_core_size; addr+=4) {
		*(unsigned int*)(addr) = addr;
		if (*(unsigned int*)(addr) != addr) {
			printf("Core %d: mem[%p] == %p != %p\n", get_id(), addr, (*(unsigned int*)(addr)), addr);
		}
	}

        barrier(barr);

	const unsigned int RW_SHARED_START = 0x51000000;
	const unsigned int RW_SHARED_SIZE  = 0x00100000;

	if (get_id() == 0) { printf("========== Phase 4 (core 0 writes data) ==========\n"); }
	// Core 0 writes data to 0x51000000-0x51100000
	if (get_id() == 0) { // Core 0
		for (unsigned int offset = 0; offset <RW_SHARED_SIZE; offset+=4) {
			unsigned int addr = RW_SHARED_START + offset;
			int data = get_id()*0x10000000 + offset;
			*(unsigned int*)(addr) = data;
		}
	}
	else { // Core 1/2/3
	}
        barrier(barr);
	for (unsigned int offset = 0; offset <RW_SHARED_SIZE; offset+=4) {
		unsigned int addr = RW_SHARED_START + offset;
		int data = 0*0x10000000 + offset;
		if (*(unsigned int*)(addr) != data) {
			printf("Core %d: mem[%p] == %p != %p\n", get_id(), addr, (*(unsigned int*)(addr)), data);
		}
	}
        barrier(barr);

	if (get_id() == 0) { printf("========== Phase 5 (core 1 writes data) ==========\n"); }
	// Core 1 writes data to 0x51000000-0x51100000
	if (get_id() == 1) { // Core 1
		for (unsigned int offset = 0; offset <RW_SHARED_SIZE; offset+=4) {
			unsigned int addr = RW_SHARED_START + offset;
			int data = get_id()*0x10000000 + offset;
			*(unsigned int*)(addr) = data;
		}
	}
	else { // Core 0/2/3
	}
        barrier(barr);
	for (unsigned int offset = 0; offset <RW_SHARED_SIZE; offset+=4) {
		unsigned int addr = RW_SHARED_START + offset;
		int data = 1*0x10000000 + offset;
		if (*(unsigned int*)(addr) != data) {
			printf("Core %d: mem[%p] == %p != %p\n", get_id(), addr, (*(unsigned int*)(addr)), data);
		}
	}
        barrier(barr);

	if (get_id() == 0) { printf("========== Phase 6 (core 2 writes data) ==========\n"); }
	// Core 2 writes data to 0x51000000-0x51100000
	if (get_id() == 2) { // Core 2
		for (unsigned int offset = 0; offset <RW_SHARED_SIZE; offset+=4) {
			unsigned int addr = RW_SHARED_START + offset;
			int data = get_id()*0x10000000 + offset;
			*(unsigned int*)(addr) = data;
		}
	}
	else { // Core 0/1/3
	}
        barrier(barr);
	for (unsigned int offset = 0; offset <RW_SHARED_SIZE; offset+=4) {
		unsigned int addr = RW_SHARED_START + offset;
		int data = 2*0x10000000 + offset;
		if (*(unsigned int*)(addr) != data) {
			printf("Core %d: mem[%p] == %p != %p\n", get_id(), addr, (*(unsigned int*)(addr)), data);
		}
	}
        barrier(barr);

	if (get_id() == 0) { printf("========== Phase 7 (core 3 writes data) ==========\n"); }
	// Core 2 writes data to 0x51000000-0x51100000
	if (get_id() == 2) { // Core 3
		for (unsigned int offset = 0; offset <RW_SHARED_SIZE; offset+=4) {
			unsigned int addr = RW_SHARED_START + offset;
			int data = get_id()*0x10000000 + offset;
			*(unsigned int*)(addr) = data;
		}
	}
	else { // Core 0/1/2
	}
        barrier(barr);
	for (unsigned int offset = 0; offset <RW_SHARED_SIZE; offset+=4) {
		unsigned int addr = RW_SHARED_START + offset;
		int data = 2*0x10000000 + offset;
		if (*(unsigned int*)(addr) != data) {
			printf("Core %d: mem[%p] == %p != %p\n", get_id(), addr, (*(unsigned int*)(addr)), data);
		}
	}
        barrier(barr);

}

int main() {
	mem_test();
  return 0;
}
