FILE(GLOB src *.cpp)
add_executable(pooling_sw_test ${src} ${CXX_SYS_OBJS})
target_link_libraries(pooling_sw_test stdc++ m c ac_sysc utility)
