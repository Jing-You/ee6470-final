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
include src/pool_engine/CMakeFiles/pool_engine.dir/depend.make

# Include the progress variables for this target.
include src/pool_engine/CMakeFiles/pool_engine.dir/progress.make

# Include the compile flags for this target's objects.
include src/pool_engine/CMakeFiles/pool_engine.dir/flags.make

src/pool_engine/CMakeFiles/pool_engine.dir/pool_engine.cpp.o: src/pool_engine/CMakeFiles/pool_engine.dir/flags.make
src/pool_engine/CMakeFiles/pool_engine.dir/pool_engine.cpp.o: ../src/pool_engine/pool_engine.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/platform/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/pool_engine/CMakeFiles/pool_engine.dir/pool_engine.cpp.o"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/pool_engine && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pool_engine.dir/pool_engine.cpp.o -c /home/u105/u105061255/ee6470/lab09/platform/src/pool_engine/pool_engine.cpp

src/pool_engine/CMakeFiles/pool_engine.dir/pool_engine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pool_engine.dir/pool_engine.cpp.i"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/pool_engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/u105/u105061255/ee6470/lab09/platform/src/pool_engine/pool_engine.cpp > CMakeFiles/pool_engine.dir/pool_engine.cpp.i

src/pool_engine/CMakeFiles/pool_engine.dir/pool_engine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pool_engine.dir/pool_engine.cpp.s"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/pool_engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/u105/u105061255/ee6470/lab09/platform/src/pool_engine/pool_engine.cpp -o CMakeFiles/pool_engine.dir/pool_engine.cpp.s

# Object files for target pool_engine
pool_engine_OBJECTS = \
"CMakeFiles/pool_engine.dir/pool_engine.cpp.o"

# External object files for target pool_engine
pool_engine_EXTERNAL_OBJECTS =

src/pool_engine/libpool_engine.a: src/pool_engine/CMakeFiles/pool_engine.dir/pool_engine.cpp.o
src/pool_engine/libpool_engine.a: src/pool_engine/CMakeFiles/pool_engine.dir/build.make
src/pool_engine/libpool_engine.a: src/pool_engine/CMakeFiles/pool_engine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/u105/u105061255/ee6470/lab09/platform/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libpool_engine.a"
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/pool_engine && $(CMAKE_COMMAND) -P CMakeFiles/pool_engine.dir/cmake_clean_target.cmake
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/pool_engine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pool_engine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/pool_engine/CMakeFiles/pool_engine.dir/build: src/pool_engine/libpool_engine.a

.PHONY : src/pool_engine/CMakeFiles/pool_engine.dir/build

src/pool_engine/CMakeFiles/pool_engine.dir/clean:
	cd /home/u105/u105061255/ee6470/lab09/platform/build/src/pool_engine && $(CMAKE_COMMAND) -P CMakeFiles/pool_engine.dir/cmake_clean.cmake
.PHONY : src/pool_engine/CMakeFiles/pool_engine.dir/clean

src/pool_engine/CMakeFiles/pool_engine.dir/depend:
	cd /home/u105/u105061255/ee6470/lab09/platform/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/u105/u105061255/ee6470/lab09/platform /home/u105/u105061255/ee6470/lab09/platform/src/pool_engine /home/u105/u105061255/ee6470/lab09/platform/build /home/u105/u105061255/ee6470/lab09/platform/build/src/pool_engine /home/u105/u105061255/ee6470/lab09/platform/build/src/pool_engine/CMakeFiles/pool_engine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/pool_engine/CMakeFiles/pool_engine.dir/depend

