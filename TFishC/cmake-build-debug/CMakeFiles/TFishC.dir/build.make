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
CMAKE_SOURCE_DIR = /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TFishC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TFishC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TFishC.dir/flags.make

CMakeFiles/TFishC.dir/main.c.o: CMakeFiles/TFishC.dir/flags.make
CMakeFiles/TFishC.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TFishC.dir/main.c.o"
	C:/cygwin64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TFishC.dir/main.c.o   -c /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/main.c

CMakeFiles/TFishC.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TFishC.dir/main.c.i"
	C:/cygwin64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/main.c > CMakeFiles/TFishC.dir/main.c.i

CMakeFiles/TFishC.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TFishC.dir/main.c.s"
	C:/cygwin64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/main.c -o CMakeFiles/TFishC.dir/main.c.s

CMakeFiles/TFishC.dir/T2F.c.o: CMakeFiles/TFishC.dir/flags.make
CMakeFiles/TFishC.dir/T2F.c.o: ../T2F.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TFishC.dir/T2F.c.o"
	C:/cygwin64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/TFishC.dir/T2F.c.o   -c /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/T2F.c

CMakeFiles/TFishC.dir/T2F.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/TFishC.dir/T2F.c.i"
	C:/cygwin64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/T2F.c > CMakeFiles/TFishC.dir/T2F.c.i

CMakeFiles/TFishC.dir/T2F.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/TFishC.dir/T2F.c.s"
	C:/cygwin64/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/T2F.c -o CMakeFiles/TFishC.dir/T2F.c.s

# Object files for target TFishC
TFishC_OBJECTS = \
"CMakeFiles/TFishC.dir/main.c.o" \
"CMakeFiles/TFishC.dir/T2F.c.o"

# External object files for target TFishC
TFishC_EXTERNAL_OBJECTS =

TFishC.exe: CMakeFiles/TFishC.dir/main.c.o
TFishC.exe: CMakeFiles/TFishC.dir/T2F.c.o
TFishC.exe: CMakeFiles/TFishC.dir/build.make
TFishC.exe: CMakeFiles/TFishC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable TFishC.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TFishC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TFishC.dir/build: TFishC.exe

.PHONY : CMakeFiles/TFishC.dir/build

CMakeFiles/TFishC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TFishC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TFishC.dir/clean

CMakeFiles/TFishC.dir/depend:
	cd /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/cmake-build-debug /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/cmake-build-debug /cygdrive/c/Users/MI/Documents/GitHub/PAZI/TFishC/cmake-build-debug/CMakeFiles/TFishC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TFishC.dir/depend

