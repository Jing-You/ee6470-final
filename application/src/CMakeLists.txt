# libraries
add_subdirectory(libac_sysc)
SET(SYSC_PLATFORM_DIR ${CMAKE_SOURCE_DIR}/../platform/src)
add_subdirectory(systemc_io_lib)

include_directories(utility)


SET(RV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rv_hal)
SET(C_SYS_OBJS ${RV_DIR}/c_crt.S
               ${RV_DIR}/get_id.S)
SET(CXX_SYS_OBJS ${RV_DIR}/cxx_crt.S
                 ${RV_DIR}/get_id.S
                 ${STARTFILES})

# executables
add_subdirectory(utility)
# add_subdirectory(pi_mp)
# add_subdirectory(heated_plate)
# add_subdirectory(mem_test_03_shared)

# add_subdirectory(hello)
# add_subdirectory(pooling_sw_test)
# add_subdirectory(pooling_hw_test)
# add_subdirectory(emboss_sw)
add_subdirectory(parallelbfs)
add_subdirectory(bfs)
