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
include src/system/CMakeFiles/isasimtest.dir/depend.make

# Include the progress variables for this target.
include src/system/CMakeFiles/isasimtest.dir/progress.make

# Include the compile flags for this target's objects.
include src/system/CMakeFiles/isasimtest.dir/flags.make

src/system/CMakeFiles/isasimtest.dir/ISASimPlatform.cpp.o: src/system/CMakeFiles/isasimtest.dir/flags.make
src/system/CMakeFiles/isasimtest.dir/ISASimPlatform.cpp.o: ../src/system/ISASimPlatform.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/platform/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/system/CMakeFiles/isasimtest.dir/ISASimPlatform.cpp.o"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/system && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/isasimtest.dir/ISASimPlatform.cpp.o -c /home/u105/u105061255/ee6470/lab09/platform/src/system/ISASimPlatform.cpp

src/system/CMakeFiles/isasimtest.dir/ISASimPlatform.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/isasimtest.dir/ISASimPlatform.cpp.i"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/system && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/u105/u105061255/ee6470/lab09/platform/src/system/ISASimPlatform.cpp > CMakeFiles/isasimtest.dir/ISASimPlatform.cpp.i

src/system/CMakeFiles/isasimtest.dir/ISASimPlatform.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/isasimtest.dir/ISASimPlatform.cpp.s"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/system && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/u105/u105061255/ee6470/lab09/platform/src/system/ISASimPlatform.cpp -o CMakeFiles/isasimtest.dir/ISASimPlatform.cpp.s

src/system/CMakeFiles/isasimtest.dir/ISASimTest.cpp.o: src/system/CMakeFiles/isasimtest.dir/flags.make
src/system/CMakeFiles/isasimtest.dir/ISASimTest.cpp.o: ../src/system/ISASimTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/platform/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/system/CMakeFiles/isasimtest.dir/ISASimTest.cpp.o"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/system && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/isasimtest.dir/ISASimTest.cpp.o -c /home/u105/u105061255/ee6470/lab09/platform/src/system/ISASimTest.cpp

src/system/CMakeFiles/isasimtest.dir/ISASimTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/isasimtest.dir/ISASimTest.cpp.i"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/system && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/u105/u105061255/ee6470/lab09/platform/src/system/ISASimTest.cpp > CMakeFiles/isasimtest.dir/ISASimTest.cpp.i

src/system/CMakeFiles/isasimtest.dir/ISASimTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/isasimtest.dir/ISASimTest.cpp.s"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/system && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/u105/u105061255/ee6470/lab09/platform/src/system/ISASimTest.cpp -o CMakeFiles/isasimtest.dir/ISASimTest.cpp.s

# Object files for target isasimtest
isasimtest_OBJECTS = \
"CMakeFiles/isasimtest.dir/ISASimPlatform.cpp.o" \
"CMakeFiles/isasimtest.dir/ISASimTest.cpp.o"

# External object files for target isasimtest
isasimtest_EXTERNAL_OBJECTS =

platform.out: src/system/CMakeFiles/isasimtest.dir/ISASimPlatform.cpp.o
platform.out: src/system/CMakeFiles/isasimtest.dir/ISASimTest.cpp.o
platform.out: src/system/CMakeFiles/isasimtest.dir/build.make
platform.out: src/cpu_core/libisasim.a
platform.out: src/system/libtlm_platform.a
platform.out: src/pool_engine/libpool_engine.a
platform.out: src/lock_engine/liblock_engine.a
platform.out: src/dma/libdma_engine.a
platform.out: src/reg_set/libreg_group.a
platform.out: src/memory/libmemory.a
platform.out: src/ctrler_api/libreg_ctl.a
platform.out: src/common/libcommon_lib.a
platform.out: src/system/CMakeFiles/isasimtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/u105/u105061255/ee6470/lab09/platform/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../platform.out"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/system && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/isasimtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/system/CMakeFiles/isasimtest.dir/build: platform.out

.PHONY : src/system/CMakeFiles/isasimtest.dir/build

src/system/CMakeFiles/isasimtest.dir/clean:
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/system && $(CMAKE_COMMAND) -P CMakeFiles/isasimtest.dir/cmake_clean.cmake
.PHONY : src/system/CMakeFiles/isasimtest.dir/clean

src/system/CMakeFiles/isasimtest.dir/depend:
	cd /home/u105/u105061255/ee6470/lab09/platform/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/u105/u105061255/ee6470/lab09/platform /home/u105/u105061255/ee6470/lab09/platform/src/system /home/u105/u105061255/ee6470/lab09/platform/build /home/u105/u105061255/ee6470/lab09/platform/build/src/system /home/u105/u105061255/ee6470/lab09/platform/build/src/system/CMakeFiles/isasimtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/system/CMakeFiles/isasimtest.dir/depend

