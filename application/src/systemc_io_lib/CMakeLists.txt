FILE(GLOB src ${SYSC_PLATFORM_DIR}/ctrler_api/*.cpp
              ${SYSC_PLATFORM_DIR}/common/utility_class.cpp)
include_directories(${SYSC_PLATFORM_DIR})
# note that -std=c++11 results uint not a defined type
SET(CMAKE_CXX_FLAGS "-O2 -march=rv32ima -mabi=ilp32")
add_library(hardwareio ${src})
