# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/ckj/my_github/boost_websocket/server/sync

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ckj/my_github/boost_websocket/server/sync/build

# Include any dependencies generated for this target.
include CMakeFiles/http-server-sync.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/http-server-sync.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/http-server-sync.dir/flags.make

CMakeFiles/http-server-sync.dir/http_server_sync.o: CMakeFiles/http-server-sync.dir/flags.make
CMakeFiles/http-server-sync.dir/http_server_sync.o: ../http_server_sync.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ckj/my_github/boost_websocket/server/sync/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/http-server-sync.dir/http_server_sync.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/http-server-sync.dir/http_server_sync.o -c /home/ckj/my_github/boost_websocket/server/sync/http_server_sync.cpp

CMakeFiles/http-server-sync.dir/http_server_sync.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/http-server-sync.dir/http_server_sync.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ckj/my_github/boost_websocket/server/sync/http_server_sync.cpp > CMakeFiles/http-server-sync.dir/http_server_sync.i

CMakeFiles/http-server-sync.dir/http_server_sync.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/http-server-sync.dir/http_server_sync.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ckj/my_github/boost_websocket/server/sync/http_server_sync.cpp -o CMakeFiles/http-server-sync.dir/http_server_sync.s

# Object files for target http-server-sync
http__server__sync_OBJECTS = \
"CMakeFiles/http-server-sync.dir/http_server_sync.o"

# External object files for target http-server-sync
http__server__sync_EXTERNAL_OBJECTS =

http-server-sync: CMakeFiles/http-server-sync.dir/http_server_sync.o
http-server-sync: CMakeFiles/http-server-sync.dir/build.make
http-server-sync: CMakeFiles/http-server-sync.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ckj/my_github/boost_websocket/server/sync/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable http-server-sync"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/http-server-sync.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/http-server-sync.dir/build: http-server-sync

.PHONY : CMakeFiles/http-server-sync.dir/build

CMakeFiles/http-server-sync.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/http-server-sync.dir/cmake_clean.cmake
.PHONY : CMakeFiles/http-server-sync.dir/clean

CMakeFiles/http-server-sync.dir/depend:
	cd /home/ckj/my_github/boost_websocket/server/sync/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ckj/my_github/boost_websocket/server/sync /home/ckj/my_github/boost_websocket/server/sync /home/ckj/my_github/boost_websocket/server/sync/build /home/ckj/my_github/boost_websocket/server/sync/build /home/ckj/my_github/boost_websocket/server/sync/build/CMakeFiles/http-server-sync.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/http-server-sync.dir/depend

