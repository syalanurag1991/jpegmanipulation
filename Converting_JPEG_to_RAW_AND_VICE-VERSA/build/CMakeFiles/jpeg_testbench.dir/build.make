# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/anuragsyal/Downloads/JPEG/Problem3_PartB/build

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/anuragsyal/Downloads/JPEG/Problem3_PartB/build

# Include any dependencies generated for this target.
include CMakeFiles/jpeg_testbench.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/jpeg_testbench.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/jpeg_testbench.dir/flags.make

CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o: CMakeFiles/jpeg_testbench.dir/flags.make
CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o: /home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/anuragsyal/Downloads/JPEG/Problem3_PartB/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o   -c /home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c

CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c > CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.i

CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c -o CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.s

CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o.requires:

.PHONY : CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o.requires

CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o.provides: CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o.requires
	$(MAKE) -f CMakeFiles/jpeg_testbench.dir/build.make CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o.provides.build
.PHONY : CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o.provides

CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o.provides.build: CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o


# Object files for target jpeg_testbench
jpeg_testbench_OBJECTS = \
"CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o"

# External object files for target jpeg_testbench
jpeg_testbench_EXTERNAL_OBJECTS =

jpeg_testbench: CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o
jpeg_testbench: CMakeFiles/jpeg_testbench.dir/build.make
jpeg_testbench: CMakeFiles/jpeg_testbench.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/anuragsyal/Downloads/JPEG/Problem3_PartB/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable jpeg_testbench"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/jpeg_testbench.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/jpeg_testbench.dir/build: jpeg_testbench

.PHONY : CMakeFiles/jpeg_testbench.dir/build

CMakeFiles/jpeg_testbench.dir/requires: CMakeFiles/jpeg_testbench.dir/home/anuragsyal/Downloads/JPEG/Problem3_PartB/src/main.c.o.requires

.PHONY : CMakeFiles/jpeg_testbench.dir/requires

CMakeFiles/jpeg_testbench.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/jpeg_testbench.dir/cmake_clean.cmake
.PHONY : CMakeFiles/jpeg_testbench.dir/clean

CMakeFiles/jpeg_testbench.dir/depend:
	cd /home/anuragsyal/Downloads/JPEG/Problem3_PartB/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/anuragsyal/Downloads/JPEG/Problem3_PartB/build /home/anuragsyal/Downloads/JPEG/Problem3_PartB/build /home/anuragsyal/Downloads/JPEG/Problem3_PartB/build /home/anuragsyal/Downloads/JPEG/Problem3_PartB/build /home/anuragsyal/Downloads/JPEG/Problem3_PartB/build/CMakeFiles/jpeg_testbench.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/jpeg_testbench.dir/depend
