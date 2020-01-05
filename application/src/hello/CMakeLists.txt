FILE(GLOB src *.cpp)
add_executable(hello ${src} ${CXX_SYS_OBJS})
target_link_libraries(hello stdc++ m c ac_sysc utility)
