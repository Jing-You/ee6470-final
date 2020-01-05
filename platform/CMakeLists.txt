cmake_minimum_required(VERSION 3.0)

## set cmake option
set(USE_HALF_FLOAT OFF)
if(${USE_HALF_FLOAT})
  set(LLVM_HOME "/home/cwchang/lib/llvm60")
  set(CMAKE_CXX_COMPILER "${LLVM_HOME}/bin/clang++")
  set(CMAKE_C_COMPILER "${LLVM_HOME}/bin/clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D USE_HALF_FLOAT")
endif(${USE_HALF_FLOAT})

OPTION(DEBUG "Print debugging information while simulation." OFF)
if(DEBUG)
  add_definitions(-DDEBUG)
  message("** Debugging mode is on. **")
endif(DEBUG)

set(PROJECT_NAME ml_hw_acc_esl_platform)
project(${PROJECT_NAME} CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

## config compile
set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_BUILD_TYPE "DEBUG")
set(CMAKE_CXX_STANDARD 14)
## set library root
set(SYSTEMC_ROOT $ENV{SYSTEMC_HOME})
set(SCML_ROOT $ENV{SCML_HOME})
set(ARCHC_ROOT $ENV{ARCHC_HOME})

set(SYSTEMC_INCLUDE64_DIR ${SYSTEMC_ROOT}/include)
set(SYSTEMC_LIB64_DIR -L${SYSTEMC_ROOT}/lib)
set(SYSTEMC_LIBRARIES systemc)

set(SCML_INCLUDE64_DIR ${SCML_ROOT}/include)
set(SCML_LIB64_DIR -L${SCML_ROOT}/lib-linux64)
set(SCML_LIBRARIES scml)

set(ARCHC_INCLUDE64_DIR ${ARCHC_ROOT}/include)
set(ARCHC_LIB64_DIR -L${ARCHC_ROOT}/lib)
set(ARCHC_LIBRARIES archc)

add_subdirectory(src)
