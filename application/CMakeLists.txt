cmake_minimum_required(VERSION 3.0)
SET(CMAKE_TOOLCHAIN_FILE cmake/Toolchain-archc-riscv.cmake
  CACHE FILEPATH "The crosscompiler setting file")

project(riscv_app C CXX ASM)
SET(CMAKE_BUILD_TYPE "DEBUG")
SET(CMAKE_C_FLAGS_DEBUG "-ggdb3")
SET(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})

SET(COMMON_FLAGS "-O2 -nostartfiles -march=rv32im -mabi=ilp32")
SET(C_LINK_SCRIPT "-T ${CMAKE_SOURCE_DIR}/src/rv_hal/test.ld")
SET(CMAKE_C_FLAGS "-std=gnu99 ${COMMON_FLAGS} ${C_LINK_SCRIPT}")
SET(CMAKE_CXX_FLAGS "${COMMON_FLAGS} -std=c++14")
SET(CMAKE_ASM_FLAGS "-march=rv32im")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_subdirectory(src)
