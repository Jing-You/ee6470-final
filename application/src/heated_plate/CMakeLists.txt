FILE(GLOB src *.c)
add_executable(heated_plate ${src} ${C_SYS_OBJS})
target_link_libraries(heated_plate c m ac_sysc utility)
