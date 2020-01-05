FILE(GLOB src *.c)
add_executable(mem_test_03_shared ${src} ${C_SYS_OBJS})
target_link_libraries(mem_test_03_shared c m ac_sysc utility)
