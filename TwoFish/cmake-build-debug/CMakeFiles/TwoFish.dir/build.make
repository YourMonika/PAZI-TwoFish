# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /cygdrive/c/Users/MI/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/MI/.CLion2019.2/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TwoFish.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TwoFish.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TwoFish.dir/flags.make

CMakeFiles/TwoFish.dir/main.cpp.o: CMakeFiles/TwoFish.dir/flags.make
CMakeFiles/TwoFish.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TwoFish.dir/main.cpp.o"
	C:/cygwin64/bin/g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TwoFish.dir/main.cpp.o -c /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/main.cpp

CMakeFiles/TwoFish.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TwoFish.dir/main.cpp.i"
	C:/cygwin64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/main.cpp > CMakeFiles/TwoFish.dir/main.cpp.i

CMakeFiles/TwoFish.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TwoFish.dir/main.cpp.s"
	C:/cygwin64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/main.cpp -o CMakeFiles/TwoFish.dir/main.cpp.s

CMakeFiles/TwoFish.dir/TwoFish.cpp.o: CMakeFiles/TwoFish.dir/flags.make
CMakeFiles/TwoFish.dir/TwoFish.cpp.o: ../TwoFish.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TwoFish.dir/TwoFish.cpp.o"
	C:/cygwin64/bin/g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TwoFish.dir/TwoFish.cpp.o -c /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/TwoFish.cpp

CMakeFiles/TwoFish.dir/TwoFish.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TwoFish.dir/TwoFish.cpp.i"
	C:/cygwin64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/TwoFish.cpp > CMakeFiles/TwoFish.dir/TwoFish.cpp.i

CMakeFiles/TwoFish.dir/TwoFish.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TwoFish.dir/TwoFish.cpp.s"
	C:/cygwin64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/TwoFish.cpp -o CMakeFiles/TwoFish.dir/TwoFish.cpp.s

# Object files for target TwoFish
TwoFish_OBJECTS = \
"CMakeFiles/TwoFish.dir/main.cpp.o" \
"CMakeFiles/TwoFish.dir/TwoFish.cpp.o"

# External object files for target TwoFish
TwoFish_EXTERNAL_OBJECTS =

TwoFish.exe: CMakeFiles/TwoFish.dir/main.cpp.o
TwoFish.exe: CMakeFiles/TwoFish.dir/TwoFish.cpp.o
TwoFish.exe: CMakeFiles/TwoFish.dir/build.make
TwoFish.exe: CMakeFiles/TwoFish.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable TwoFish.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TwoFish.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TwoFish.dir/build: TwoFish.exe

.PHONY : CMakeFiles/TwoFish.dir/build

CMakeFiles/TwoFish.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TwoFish.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TwoFish.dir/clean

CMakeFiles/TwoFish.dir/depend:
	cd /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/cmake-build-debug /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/cmake-build-debug /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TwoFish/cmake-build-debug/CMakeFiles/TwoFish.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TwoFish.dir/depend

