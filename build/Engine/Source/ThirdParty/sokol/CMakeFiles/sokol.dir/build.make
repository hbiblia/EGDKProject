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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /d/Github/EGDK_/EGDKProyect

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /d/Github/EGDK_/EGDKProyect/build

# Include any dependencies generated for this target.
include Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/compiler_depend.make

# Include the progress variables for this target.
include Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/progress.make

# Include the compile flags for this target's objects.
include Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/flags.make

Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/sokol_impl.c.obj: Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/flags.make
Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/sokol_impl.c.obj: ../Engine/Source/ThirdParty/sokol/sokol_impl.c
Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/sokol_impl.c.obj: Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/d/Github/EGDK_/EGDKProyect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/sokol_impl.c.obj"
	cd /d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/sokol && /mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/sokol_impl.c.obj -MF CMakeFiles/sokol.dir/sokol_impl.c.obj.d -o CMakeFiles/sokol.dir/sokol_impl.c.obj -c /d/Github/EGDK_/EGDKProyect/Engine/Source/ThirdParty/sokol/sokol_impl.c

Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/sokol_impl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/sokol.dir/sokol_impl.c.i"
	cd /d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/sokol && /mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /d/Github/EGDK_/EGDKProyect/Engine/Source/ThirdParty/sokol/sokol_impl.c > CMakeFiles/sokol.dir/sokol_impl.c.i

Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/sokol_impl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/sokol.dir/sokol_impl.c.s"
	cd /d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/sokol && /mingw64/bin/cc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /d/Github/EGDK_/EGDKProyect/Engine/Source/ThirdParty/sokol/sokol_impl.c -o CMakeFiles/sokol.dir/sokol_impl.c.s

# Object files for target sokol
sokol_OBJECTS = \
"CMakeFiles/sokol.dir/sokol_impl.c.obj"

# External object files for target sokol
sokol_EXTERNAL_OBJECTS =

Engine/Source/ThirdParty/sokol/libsokol.a: Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/sokol_impl.c.obj
Engine/Source/ThirdParty/sokol/libsokol.a: Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/build.make
Engine/Source/ThirdParty/sokol/libsokol.a: Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/d/Github/EGDK_/EGDKProyect/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libsokol.a"
	cd /d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/sokol && $(CMAKE_COMMAND) -P CMakeFiles/sokol.dir/cmake_clean_target.cmake
	cd /d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/sokol && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sokol.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/build: Engine/Source/ThirdParty/sokol/libsokol.a
.PHONY : Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/build

Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/clean:
	cd /d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/sokol && $(CMAKE_COMMAND) -P CMakeFiles/sokol.dir/cmake_clean.cmake
.PHONY : Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/clean

Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/depend:
	cd /d/Github/EGDK_/EGDKProyect/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /d/Github/EGDK_/EGDKProyect /d/Github/EGDK_/EGDKProyect/Engine/Source/ThirdParty/sokol /d/Github/EGDK_/EGDKProyect/build /d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/sokol /d/Github/EGDK_/EGDKProyect/build/Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Engine/Source/ThirdParty/sokol/CMakeFiles/sokol.dir/depend
