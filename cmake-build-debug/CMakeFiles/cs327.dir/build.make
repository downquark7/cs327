# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/downq/CLionProjects/cs327

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/downq/CLionProjects/cs327/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cs327.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cs327.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cs327.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cs327.dir/flags.make

CMakeFiles/cs327.dir/listKnights.c.o: CMakeFiles/cs327.dir/flags.make
CMakeFiles/cs327.dir/listKnights.c.o: ../listKnights.c
CMakeFiles/cs327.dir/listKnights.c.o: CMakeFiles/cs327.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/downq/CLionProjects/cs327/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cs327.dir/listKnights.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/cs327.dir/listKnights.c.o -MF CMakeFiles/cs327.dir/listKnights.c.o.d -o CMakeFiles/cs327.dir/listKnights.c.o -c /mnt/c/Users/downq/CLionProjects/cs327/listKnights.c

CMakeFiles/cs327.dir/listKnights.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cs327.dir/listKnights.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/downq/CLionProjects/cs327/listKnights.c > CMakeFiles/cs327.dir/listKnights.c.i

CMakeFiles/cs327.dir/listKnights.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cs327.dir/listKnights.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/downq/CLionProjects/cs327/listKnights.c -o CMakeFiles/cs327.dir/listKnights.c.s

# Object files for target cs327
cs327_OBJECTS = \
"CMakeFiles/cs327.dir/listKnights.c.o"

# External object files for target cs327
cs327_EXTERNAL_OBJECTS =

cs327: CMakeFiles/cs327.dir/listKnights.c.o
cs327: CMakeFiles/cs327.dir/build.make
cs327: CMakeFiles/cs327.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/downq/CLionProjects/cs327/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable cs327"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cs327.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cs327.dir/build: cs327
.PHONY : CMakeFiles/cs327.dir/build

CMakeFiles/cs327.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cs327.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cs327.dir/clean

CMakeFiles/cs327.dir/depend:
	cd /mnt/c/Users/downq/CLionProjects/cs327/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/downq/CLionProjects/cs327 /mnt/c/Users/downq/CLionProjects/cs327 /mnt/c/Users/downq/CLionProjects/cs327/cmake-build-debug /mnt/c/Users/downq/CLionProjects/cs327/cmake-build-debug /mnt/c/Users/downq/CLionProjects/cs327/cmake-build-debug/CMakeFiles/cs327.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cs327.dir/depend

