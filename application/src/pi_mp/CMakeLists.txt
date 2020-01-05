FILE(GLOB src *.c)
add_executable(pi_mp ${src} ${C_SYS_OBJS})
target_link_libraries(pi_mp c m ac_sysc utility)
