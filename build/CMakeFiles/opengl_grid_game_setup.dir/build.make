# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/miles/dev/platformer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/miles/dev/platformer/build

# Include any dependencies generated for this target.
include CMakeFiles/opengl_grid_game_setup.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/opengl_grid_game_setup.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/opengl_grid_game_setup.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/opengl_grid_game_setup.dir/flags.make

CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.o: CMakeFiles/opengl_grid_game_setup.dir/flags.make
CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.o: /home/miles/dev/platformer/src/main.cpp
CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.o: CMakeFiles/opengl_grid_game_setup.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/miles/dev/platformer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.o -MF CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.o.d -o CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.o -c /home/miles/dev/platformer/src/main.cpp

CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/miles/dev/platformer/src/main.cpp > CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.i

CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/miles/dev/platformer/src/main.cpp -o CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.s

CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.o: CMakeFiles/opengl_grid_game_setup.dir/flags.make
CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.o: /home/miles/dev/platformer/src/glad.c
CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.o: CMakeFiles/opengl_grid_game_setup.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/miles/dev/platformer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.o -MF CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.o.d -o CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.o -c /home/miles/dev/platformer/src/glad.c

CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/miles/dev/platformer/src/glad.c > CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.i

CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/miles/dev/platformer/src/glad.c -o CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.s

# Object files for target opengl_grid_game_setup
opengl_grid_game_setup_OBJECTS = \
"CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.o" \
"CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.o"

# External object files for target opengl_grid_game_setup
opengl_grid_game_setup_EXTERNAL_OBJECTS =

opengl_grid_game_setup: CMakeFiles/opengl_grid_game_setup.dir/src/main.cpp.o
opengl_grid_game_setup: CMakeFiles/opengl_grid_game_setup.dir/src/glad.c.o
opengl_grid_game_setup: CMakeFiles/opengl_grid_game_setup.dir/build.make
opengl_grid_game_setup: CMakeFiles/opengl_grid_game_setup.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/miles/dev/platformer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable opengl_grid_game_setup"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opengl_grid_game_setup.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/opengl_grid_game_setup.dir/build: opengl_grid_game_setup
.PHONY : CMakeFiles/opengl_grid_game_setup.dir/build

CMakeFiles/opengl_grid_game_setup.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/opengl_grid_game_setup.dir/cmake_clean.cmake
.PHONY : CMakeFiles/opengl_grid_game_setup.dir/clean

CMakeFiles/opengl_grid_game_setup.dir/depend:
	cd /home/miles/dev/platformer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/miles/dev/platformer /home/miles/dev/platformer /home/miles/dev/platformer/build /home/miles/dev/platformer/build /home/miles/dev/platformer/build/CMakeFiles/opengl_grid_game_setup.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/opengl_grid_game_setup.dir/depend

