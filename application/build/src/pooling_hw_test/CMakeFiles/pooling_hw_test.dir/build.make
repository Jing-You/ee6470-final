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
CMAKE_SOURCE_DIR = /home/u105/u105061255/ee6470/lab09/application

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/u105/u105061255/ee6470/lab09/application/build

# Include any dependencies generated for this target.
include src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/depend.make

# Include the progress variables for this target.
include src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/progress.make

# Include the compile flags for this target's objects.
include src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/flags.make

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/main.cpp.obj: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/flags.make
src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/main.cpp.obj: ../src/pooling_hw_test/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/main.cpp.obj"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pooling_hw_test.dir/main.cpp.obj -c /home/u105/u105061255/ee6470/lab09/application/src/pooling_hw_test/main.cpp

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pooling_hw_test.dir/main.cpp.i"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/u105/u105061255/ee6470/lab09/application/src/pooling_hw_test/main.cpp > CMakeFiles/pooling_hw_test.dir/main.cpp.i

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pooling_hw_test.dir/main.cpp.s"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/u105/u105061255/ee6470/lab09/application/src/pooling_hw_test/main.cpp -o CMakeFiles/pooling_hw_test.dir/main.cpp.s

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp.obj: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/flags.make
src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp.obj: /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp.obj"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp.obj -c /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp.i"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp > CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp.i

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp.s"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp -o CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp.s

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp.obj: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/flags.make
src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp.obj: /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp.obj"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp.obj -c /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp.i"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp > CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp.i

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp.s"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp -o CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp.s

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp.obj: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/flags.make
src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp.obj: /home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp.obj"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp.obj -c /home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp.i"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp > CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp.i

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp.s"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp -o CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp.s

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/__/rv_hal/cxx_crt.S.obj: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/flags.make
src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/__/rv_hal/cxx_crt.S.obj: ../src/rv_hal/cxx_crt.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building ASM object src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/__/rv_hal/cxx_crt.S.obj"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/pooling_hw_test.dir/__/rv_hal/cxx_crt.S.obj -c /home/u105/u105061255/ee6470/lab09/application/src/rv_hal/cxx_crt.S

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/__/rv_hal/get_id.S.obj: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/flags.make
src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/__/rv_hal/get_id.S.obj: ../src/rv_hal/get_id.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building ASM object src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/__/rv_hal/get_id.S.obj"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/pooling_hw_test.dir/__/rv_hal/get_id.S.obj -c /home/u105/u105061255/ee6470/lab09/application/src/rv_hal/get_id.S

# Object files for target pooling_hw_test
pooling_hw_test_OBJECTS = \
"CMakeFiles/pooling_hw_test.dir/main.cpp.obj" \
"CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp.obj" \
"CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp.obj" \
"CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp.obj" \
"CMakeFiles/pooling_hw_test.dir/__/rv_hal/cxx_crt.S.obj" \
"CMakeFiles/pooling_hw_test.dir/__/rv_hal/get_id.S.obj"

# External object files for target pooling_hw_test
pooling_hw_test_EXTERNAL_OBJECTS = \
"/opt/andes-rv32-toolchain/lib/gcc/riscv32-unknown-elf/7.1.1/crtbegin.o" \
"/opt/andes-rv32-toolchain/lib/gcc/riscv32-unknown-elf/7.1.1/crtend.o"

pooling_hw_test: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/main.cpp.obj
pooling_hw_test: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/bus_access_if.cpp.obj
pooling_hw_test: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/ctrler_api/ctrler_api.cpp.obj
pooling_hw_test: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/home/u105/u105061255/ee6470/lab09/platform/src/common/utility_class.cpp.obj
pooling_hw_test: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/__/rv_hal/cxx_crt.S.obj
pooling_hw_test: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/__/rv_hal/get_id.S.obj
pooling_hw_test: /opt/andes-rv32-toolchain/lib/gcc/riscv32-unknown-elf/7.1.1/crtbegin.o
pooling_hw_test: /opt/andes-rv32-toolchain/lib/gcc/riscv32-unknown-elf/7.1.1/crtend.o
pooling_hw_test: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/build.make
pooling_hw_test: src/libac_sysc/libac_sysc.a
pooling_hw_test: src/utility/libutility.a
pooling_hw_test: src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/u105/u105061255/ee6470/lab09/application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ../../pooling_hw_test"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pooling_hw_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/build: pooling_hw_test

.PHONY : src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/build

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/clean:
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test && $(CMAKE_COMMAND) -P CMakeFiles/pooling_hw_test.dir/cmake_clean.cmake
.PHONY : src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/clean

src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/depend:
	cd /home/u105/u105061255/ee6470/lab09/application/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/u105/u105061255/ee6470/lab09/application /home/u105/u105061255/ee6470/lab09/application/src/pooling_hw_test /home/u105/u105061255/ee6470/lab09/application/build /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test /home/u105/u105061255/ee6470/lab09/application/build/src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/pooling_hw_test/CMakeFiles/pooling_hw_test.dir/depend

