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
include src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/depend.make

# Include the progress variables for this target.
include src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/progress.make

# Include the compile flags for this target's objects.
include src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/flags.make

src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/mem_test_03_shared.c.obj: src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/flags.make
src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/mem_test_03_shared.c.obj: ../src/mem_test_03_shared/mem_test_03_shared.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/mem_test_03_shared.c.obj"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/mem_test_03_shared && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mem_test_03_shared.dir/mem_test_03_shared.c.obj   -c /home/u105/u105061255/ee6470/lab09/application/src/mem_test_03_shared/mem_test_03_shared.c

src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/mem_test_03_shared.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mem_test_03_shared.dir/mem_test_03_shared.c.i"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/mem_test_03_shared && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/u105/u105061255/ee6470/lab09/application/src/mem_test_03_shared/mem_test_03_shared.c > CMakeFiles/mem_test_03_shared.dir/mem_test_03_shared.c.i

src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/mem_test_03_shared.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mem_test_03_shared.dir/mem_test_03_shared.c.s"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/mem_test_03_shared && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/u105/u105061255/ee6470/lab09/application/src/mem_test_03_shared/mem_test_03_shared.c -o CMakeFiles/mem_test_03_shared.dir/mem_test_03_shared.c.s

src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/__/rv_hal/c_crt.S.obj: src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/flags.make
src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/__/rv_hal/c_crt.S.obj: ../src/rv_hal/c_crt.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building ASM object src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/__/rv_hal/c_crt.S.obj"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/mem_test_03_shared && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/mem_test_03_shared.dir/__/rv_hal/c_crt.S.obj -c /home/u105/u105061255/ee6470/lab09/application/src/rv_hal/c_crt.S

src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/__/rv_hal/get_id.S.obj: src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/flags.make
src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/__/rv_hal/get_id.S.obj: ../src/rv_hal/get_id.S
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/u105/u105061255/ee6470/lab09/application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building ASM object src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/__/rv_hal/get_id.S.obj"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/mem_test_03_shared && /opt/andes-rv32-toolchain/bin/riscv32-unknown-elf-gcc $(ASM_DEFINES) $(ASM_INCLUDES) $(ASM_FLAGS) -o CMakeFiles/mem_test_03_shared.dir/__/rv_hal/get_id.S.obj -c /home/u105/u105061255/ee6470/lab09/application/src/rv_hal/get_id.S

# Object files for target mem_test_03_shared
mem_test_03_shared_OBJECTS = \
"CMakeFiles/mem_test_03_shared.dir/mem_test_03_shared.c.obj" \
"CMakeFiles/mem_test_03_shared.dir/__/rv_hal/c_crt.S.obj" \
"CMakeFiles/mem_test_03_shared.dir/__/rv_hal/get_id.S.obj"

# External object files for target mem_test_03_shared
mem_test_03_shared_EXTERNAL_OBJECTS =

mem_test_03_shared: src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/mem_test_03_shared.c.obj
mem_test_03_shared: src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/__/rv_hal/c_crt.S.obj
mem_test_03_shared: src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/__/rv_hal/get_id.S.obj
mem_test_03_shared: src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/build.make
mem_test_03_shared: src/libac_sysc/libac_sysc.a
mem_test_03_shared: src/utility/libutility.a
mem_test_03_shared: src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/u105/u105061255/ee6470/lab09/application/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable ../../mem_test_03_shared"
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/mem_test_03_shared && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mem_test_03_shared.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/build: mem_test_03_shared

.PHONY : src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/build

src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/clean:
	cd /home/u105/u105061255/ee6470/lab09/application/build/src/mem_test_03_shared && $(CMAKE_COMMAND) -P CMakeFiles/mem_test_03_shared.dir/cmake_clean.cmake
.PHONY : src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/clean

src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/depend:
	cd /home/u105/u105061255/ee6470/lab09/application/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/u105/u105061255/ee6470/lab09/application /home/u105/u105061255/ee6470/lab09/application/src/mem_test_03_shared /home/u105/u105061255/ee6470/lab09/application/build /home/u105/u105061255/ee6470/lab09/application/build/src/mem_test_03_shared /home/u105/u105061255/ee6470/lab09/application/build/src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/mem_test_03_shared/CMakeFiles/mem_test_03_shared.dir/depend
