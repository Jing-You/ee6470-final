# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Produce verbose output by default.
VERBOSE = 1

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/u105/u105061255/ee6470/lab09/platform

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/u105/u105061255/ee6470/lab09/platform/build

# Include any dependencies generated for this target.
include src/ctrler_api/CMakeFiles/reg_ctl.dir/depend.make

# Include the progress variables for this target.
include src/ctrler_api/CMakeFiles/reg_ctl.dir/progress.make

# Include the compile flags for this target's objects.
include src/ctrler_api/CMakeFiles/reg_ctl.dir/flags.make

src/ctrler_api/CMakeFiles/reg_ctl.dir/bus_access_if.cpp.o: src/ctrler_api/CMakeFiles/reg_ctl.dir/flags.make
src/ctrler_api/CMakeFiles/reg_ctl.dir/bus_access_if.cpp.o: ../src/ctrler_api/bus_access_if.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/platform/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/ctrler_api/CMakeFiles/reg_ctl.dir/bus_access_if.cpp.o"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/ctrler_api && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/reg_ctl.dir/bus_access_if.cpp.o -c /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp

src/ctrler_api/CMakeFiles/reg_ctl.dir/bus_access_if.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reg_ctl.dir/bus_access_if.cpp.i"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/ctrler_api && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp > CMakeFiles/reg_ctl.dir/bus_access_if.cpp.i

src/ctrler_api/CMakeFiles/reg_ctl.dir/bus_access_if.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reg_ctl.dir/bus_access_if.cpp.s"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/ctrler_api && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp -o CMakeFiles/reg_ctl.dir/bus_access_if.cpp.s

src/ctrler_api/CMakeFiles/reg_ctl.dir/ctrler_api.cpp.o: src/ctrler_api/CMakeFiles/reg_ctl.dir/flags.make
src/ctrler_api/CMakeFiles/reg_ctl.dir/ctrler_api.cpp.o: ../src/ctrler_api/ctrler_api.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/platform/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/ctrler_api/CMakeFiles/reg_ctl.dir/ctrler_api.cpp.o"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/ctrler_api && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/reg_ctl.dir/ctrler_api.cpp.o -c /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp

src/ctrler_api/CMakeFiles/reg_ctl.dir/ctrler_api.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/reg_ctl.dir/ctrler_api.cpp.i"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/ctrler_api && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp > CMakeFiles/reg_ctl.dir/ctrler_api.cpp.i

src/ctrler_api/CMakeFiles/reg_ctl.dir/ctrler_api.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/reg_ctl.dir/ctrler_api.cpp.s"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/ctrler_api && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp -o CMakeFiles/reg_ctl.dir/ctrler_api.cpp.s

# Object files for target reg_ctl
reg_ctl_OBJECTS = \
"CMakeFiles/reg_ctl.dir/bus_access_if.cpp.o" \
"CMakeFiles/reg_ctl.dir/ctrler_api.cpp.o"

# External object files for target reg_ctl
reg_ctl_EXTERNAL_OBJECTS =

src/ctrler_api/libreg_ctl.a: src/ctrler_api/CMakeFiles/reg_ctl.dir/bus_access_if.cpp.o
src/ctrler_api/libreg_ctl.a: src/ctrler_api/CMakeFiles/reg_ctl.dir/ctrler_api.cpp.o
src/ctrler_api/libreg_ctl.a: src/ctrler_api/CMakeFiles/reg_ctl.dir/build.make
src/ctrler_api/libreg_ctl.a: src/ctrler_api/CMakeFiles/reg_ctl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/u105/u105061255/ee6470/lab09/platform/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libreg_ctl.a"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/ctrler_api && $(CMAKE_COMMAND) -P CMakeFiles/reg_ctl.dir/cmake_clean_target.cmake
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/ctrler_api && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reg_ctl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/ctrler_api/CMakeFiles/reg_ctl.dir/build: src/ctrler_api/libreg_ctl.a

.PHONY : src/ctrler_api/CMakeFiles/reg_ctl.dir/build

src/ctrler_api/CMakeFiles/reg_ctl.dir/clean:
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/ctrler_api && $(CMAKE_COMMAND) -P CMakeFiles/reg_ctl.dir/cmake_clean.cmake
.PHONY : src/ctrler_api/CMakeFiles/reg_ctl.dir/clean

src/ctrler_api/CMakeFiles/reg_ctl.dir/depend:
	cd /home/u105/u105061255/ee6470/lab09/platform/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/u105/u105061255/ee6470/lab09/platform /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api /home/u105/u105061255/ee6470/lab09/platform/build /home/u105/u105061255/ee6470/lab09/platform/build/src/ctrler_api /home/u105/u105061255/ee6470/lab09/platform/build/src/ctrler_api/CMakeFiles/reg_ctl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/ctrler_api/CMakeFiles/reg_ctl.dir/depend

