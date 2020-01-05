FILE(GLOB src *.cpp)
add_executable(parallelbfs ${src} ${CXX_SYS_OBJS})
target_link_libraries(parallelbfs stdc++ m c ac_sysc utility)
