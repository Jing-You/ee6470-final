#include <iostream>

extern "C" int get_id();

extern "C" {
#include "acPthread.h"
}

int main() {
	std::cout << "Hello from CPU" << get_id() << std::endl;
}
