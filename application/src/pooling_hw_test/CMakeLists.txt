FILE(GLOB src *.cpp)

# These are the hardware register writers provided by the platform
set(platform_path ${CMAKE_SOURCE_DIR}/../platform/src)
include_directories(${platform_path})
set(platform_ctrl ${platform_path}/ctrler_api/bus_access_if.cpp ${platform_path}/ctrler_api/ctrler_api.cpp ${platform_path}/common/utility_class.cpp)

add_executable(pooling_hw_test ${src} ${platform_ctrl} ${CXX_SYS_OBJS})
target_link_libraries(pooling_hw_test stdc++ m c ac_sysc utility)
