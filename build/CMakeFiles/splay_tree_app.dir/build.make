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
CMAKE_SOURCE_DIR = /mnt/c/Users/15103/Desktop/251/work3/work

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/15103/Desktop/251/work3/work/build

# Include any dependencies generated for this target.
include CMakeFiles/splay_tree_app.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/splay_tree_app.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/splay_tree_app.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/splay_tree_app.dir/flags.make

CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.o: CMakeFiles/splay_tree_app.dir/flags.make
CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.o: ../src/splay_tree_app.cpp
CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.o: CMakeFiles/splay_tree_app.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/15103/Desktop/251/work3/work/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.o -MF CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.o.d -o CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.o -c /mnt/c/Users/15103/Desktop/251/work3/work/src/splay_tree_app.cpp

CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/15103/Desktop/251/work3/work/src/splay_tree_app.cpp > CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.i

CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/15103/Desktop/251/work3/work/src/splay_tree_app.cpp -o CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.s

# Object files for target splay_tree_app
splay_tree_app_OBJECTS = \
"CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.o"

# External object files for target splay_tree_app
splay_tree_app_EXTERNAL_OBJECTS =

splay_tree_app: CMakeFiles/splay_tree_app.dir/src/splay_tree_app.cpp.o
splay_tree_app: CMakeFiles/splay_tree_app.dir/build.make
splay_tree_app: libproject3.a
splay_tree_app: CMakeFiles/splay_tree_app.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/15103/Desktop/251/work3/work/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable splay_tree_app"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/splay_tree_app.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/splay_tree_app.dir/build: splay_tree_app
.PHONY : CMakeFiles/splay_tree_app.dir/build

CMakeFiles/splay_tree_app.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/splay_tree_app.dir/cmake_clean.cmake
.PHONY : CMakeFiles/splay_tree_app.dir/clean

CMakeFiles/splay_tree_app.dir/depend:
	cd /mnt/c/Users/15103/Desktop/251/work3/work/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/15103/Desktop/251/work3/work /mnt/c/Users/15103/Desktop/251/work3/work /mnt/c/Users/15103/Desktop/251/work3/work/build /mnt/c/Users/15103/Desktop/251/work3/work/build /mnt/c/Users/15103/Desktop/251/work3/work/build/CMakeFiles/splay_tree_app.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/splay_tree_app.dir/depend

