# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alexandremenielle/Documents/4A/C/HangmanMultiServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alexandremenielle/Documents/4A/C/HangmanMultiServer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HangmanMultiServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/HangmanMultiServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HangmanMultiServer.dir/flags.make

CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o: CMakeFiles/HangmanMultiServer.dir/flags.make
CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o: ../multi-server/multi-server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexandremenielle/Documents/4A/C/HangmanMultiServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o   -c /Users/alexandremenielle/Documents/4A/C/HangmanMultiServer/multi-server/multi-server.c

CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/alexandremenielle/Documents/4A/C/HangmanMultiServer/multi-server/multi-server.c > CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.i

CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/alexandremenielle/Documents/4A/C/HangmanMultiServer/multi-server/multi-server.c -o CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.s

CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o.requires:

.PHONY : CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o.requires

CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o.provides: CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o.requires
	$(MAKE) -f CMakeFiles/HangmanMultiServer.dir/build.make CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o.provides.build
.PHONY : CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o.provides

CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o.provides.build: CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o


# Object files for target HangmanMultiServer
HangmanMultiServer_OBJECTS = \
"CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o"

# External object files for target HangmanMultiServer
HangmanMultiServer_EXTERNAL_OBJECTS =

HangmanMultiServer: CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o
HangmanMultiServer: CMakeFiles/HangmanMultiServer.dir/build.make
HangmanMultiServer: CMakeFiles/HangmanMultiServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alexandremenielle/Documents/4A/C/HangmanMultiServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable HangmanMultiServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HangmanMultiServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HangmanMultiServer.dir/build: HangmanMultiServer

.PHONY : CMakeFiles/HangmanMultiServer.dir/build

CMakeFiles/HangmanMultiServer.dir/requires: CMakeFiles/HangmanMultiServer.dir/multi-server/multi-server.c.o.requires

.PHONY : CMakeFiles/HangmanMultiServer.dir/requires

CMakeFiles/HangmanMultiServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HangmanMultiServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HangmanMultiServer.dir/clean

CMakeFiles/HangmanMultiServer.dir/depend:
	cd /Users/alexandremenielle/Documents/4A/C/HangmanMultiServer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alexandremenielle/Documents/4A/C/HangmanMultiServer /Users/alexandremenielle/Documents/4A/C/HangmanMultiServer /Users/alexandremenielle/Documents/4A/C/HangmanMultiServer/cmake-build-debug /Users/alexandremenielle/Documents/4A/C/HangmanMultiServer/cmake-build-debug /Users/alexandremenielle/Documents/4A/C/HangmanMultiServer/cmake-build-debug/CMakeFiles/HangmanMultiServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HangmanMultiServer.dir/depend

