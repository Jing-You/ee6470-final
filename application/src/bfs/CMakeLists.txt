FILE(GLOB src *.cpp)
add_executable(bfs ${src} ${CXX_SYS_OBJS})
target_link_libraries(bfs stdc++ m c ac_sysc utility)
