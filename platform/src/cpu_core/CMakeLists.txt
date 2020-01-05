include_directories(${ARCHC_INCLUDE64_DIR})
include_directories(riscv_rv32g)

set(ARCHC_CFLAGS "-DAC_MATCH_ENDIANNESS -DAC_GUEST_BIG_ENDIAN -Wno-deprecated")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARCHC_CFLAGS}")

file(GLOB src *.cpp)
file(GLOB riscv_src riscv_rv32g/*.cpp)
list(REMOVE_ITEM riscv_src
     ${CMAKE_CURRENT_SOURCE_DIR}/riscv_rv32g/riscv_isa.cpp
     ${CMAKE_CURRENT_SOURCE_DIR}/riscv_rv32g/riscv_isa_init.cpp
)
add_library(isasim STATIC ${src} ${riscv_src})
