# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\OpenglLearn\C++\CMake\cmake-3.13.0-rc3-win64-x64\bin\cmake.exe

# The command to remove a file.
RM = D:\OpenglLearn\C++\CMake\cmake-3.13.0-rc3-win64-x64\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Git\OpenglLearn\C++\Projects\HelloWorld

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Git\OpenglLearn\C++\Projects\HelloWorld\build

# Include any dependencies generated for this target.
include CMakeFiles/helloworld.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/helloworld.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/helloworld.dir/flags.make

CMakeFiles/helloworld.dir/helloworld.cpp.obj: CMakeFiles/helloworld.dir/flags.make
CMakeFiles/helloworld.dir/helloworld.cpp.obj: ../helloworld.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Git\OpenglLearn\C++\Projects\HelloWorld\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/helloworld.dir/helloworld.cpp.obj"
	D:\OpenglLearn\C++\MinGW\x86_64-8.1.0-release-win32-seh-rt_v6-rev0\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\helloworld.dir\helloworld.cpp.obj -c D:\Git\OpenglLearn\C++\Projects\HelloWorld\helloworld.cpp

CMakeFiles/helloworld.dir/helloworld.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/helloworld.cpp.i"
	D:\OpenglLearn\C++\MinGW\x86_64-8.1.0-release-win32-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Git\OpenglLearn\C++\Projects\HelloWorld\helloworld.cpp > CMakeFiles\helloworld.dir\helloworld.cpp.i

CMakeFiles/helloworld.dir/helloworld.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/helloworld.cpp.s"
	D:\OpenglLearn\C++\MinGW\x86_64-8.1.0-release-win32-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Git\OpenglLearn\C++\Projects\HelloWorld\helloworld.cpp -o CMakeFiles\helloworld.dir\helloworld.cpp.s

# Object files for target helloworld
helloworld_OBJECTS = \
"CMakeFiles/helloworld.dir/helloworld.cpp.obj"

# External object files for target helloworld
helloworld_EXTERNAL_OBJECTS =

helloworld.exe: CMakeFiles/helloworld.dir/helloworld.cpp.obj
helloworld.exe: CMakeFiles/helloworld.dir/build.make
helloworld.exe: CMakeFiles/helloworld.dir/linklibs.rsp
helloworld.exe: CMakeFiles/helloworld.dir/objects1.rsp
helloworld.exe: CMakeFiles/helloworld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Git\OpenglLearn\C++\Projects\HelloWorld\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable helloworld.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\helloworld.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/helloworld.dir/build: helloworld.exe

.PHONY : CMakeFiles/helloworld.dir/build

CMakeFiles/helloworld.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\helloworld.dir\cmake_clean.cmake
.PHONY : CMakeFiles/helloworld.dir/clean

CMakeFiles/helloworld.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Git\OpenglLearn\C++\Projects\HelloWorld D:\Git\OpenglLearn\C++\Projects\HelloWorld D:\Git\OpenglLearn\C++\Projects\HelloWorld\build D:\Git\OpenglLearn\C++\Projects\HelloWorld\build D:\Git\OpenglLearn\C++\Projects\HelloWorld\build\CMakeFiles\helloworld.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/helloworld.dir/depend

