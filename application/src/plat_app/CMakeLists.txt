FILE(GLOB src *.cpp)
include_directories(${SYSC_PLATFORM_DIR})
add_executable(hardwareIO_test ${src} ${CXX_SYS_OBJS})
target_link_libraries(hardwareIO_test hardwareio stdc++ m c ac_sysc)
