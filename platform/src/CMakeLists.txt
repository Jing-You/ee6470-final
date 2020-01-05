include_directories(${SCML_INCLUDE64_DIR})
include_directories(${SYSTEMC_INCLUDE64_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# In theory I should use -Og to give better support of gdb
# It will makes the conv simulation a bit slower comparing to O2 (20s vs 17s)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -ggdb3 -O2")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

set(TLM_CFLAGS "-DSC_INCLUDE_FX -DUSING_TLM_SOCKET")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -m64 ${OPT_CFLAGS} ${TLM_CFLAGS}")
set(CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} -m64")

add_subdirectory(common)
add_subdirectory(reg_set)
add_subdirectory(lock_engine)
add_subdirectory(pool_engine)
add_subdirectory(dma)
add_subdirectory(memory)
add_subdirectory(ctrler_api)
add_subdirectory(system)
add_subdirectory(cpu_core)
