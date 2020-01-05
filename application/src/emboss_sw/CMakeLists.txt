FILE(GLOB src *.cpp)
add_executable(emboss_sw ${src} ${CXX_SYS_OBJS})
target_link_libraries(emboss_sw stdc++ m c ac_sysc utility)
