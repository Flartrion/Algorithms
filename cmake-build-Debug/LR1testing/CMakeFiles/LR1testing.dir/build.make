# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\LR1testing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\LR1testing

# Include any dependencies generated for this target.
include CMakeFiles/LR1testing.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LR1testing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LR1testing.dir/flags.make

CMakeFiles/LR1testing.dir/main.cpp.obj: CMakeFiles/LR1testing.dir/flags.make
CMakeFiles/LR1testing.dir/main.cpp.obj: CMakeFiles/LR1testing.dir/includes_CXX.rsp
CMakeFiles/LR1testing.dir/main.cpp.obj: C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/LR1testing/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\LR1testing\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LR1testing.dir/main.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -g -g -o CMakeFiles\LR1testing.dir\main.cpp.obj -c C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\LR1testing\main.cpp

CMakeFiles/LR1testing.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LR1testing.dir/main.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -g -g -E C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\LR1testing\main.cpp > CMakeFiles\LR1testing.dir\main.cpp.i

CMakeFiles/LR1testing.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LR1testing.dir/main.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -g -g -S C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\LR1testing\main.cpp -o CMakeFiles\LR1testing.dir\main.cpp.s

# Object files for target LR1testing
LR1testing_OBJECTS = \
"CMakeFiles/LR1testing.dir/main.cpp.obj"

# External object files for target LR1testing
LR1testing_EXTERNAL_OBJECTS =

C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR1testing.exe: CMakeFiles/LR1testing.dir/main.cpp.obj
C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR1testing.exe: CMakeFiles/LR1testing.dir/build.make
C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR1testing.exe: C:/UnitTest++/lib/libUnitTest++.a
C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR1testing.exe: C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/LR1testing/../cmake-build-Debug/output/libLR1test.a
C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR1testing.exe: CMakeFiles/LR1testing.dir/linklibs.rsp
C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR1testing.exe: CMakeFiles/LR1testing.dir/objects1.rsp
C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR1testing.exe: CMakeFiles/LR1testing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\LR1testing\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\output\LR1testing.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LR1testing.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LR1testing.dir/build: C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR1testing.exe

.PHONY : CMakeFiles/LR1testing.dir/build

CMakeFiles/LR1testing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LR1testing.dir\cmake_clean.cmake
.PHONY : CMakeFiles/LR1testing.dir/clean

CMakeFiles/LR1testing.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\LR1testing C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\LR1testing C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\LR1testing C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\LR1testing C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\LR1testing\CMakeFiles\LR1testing.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LR1testing.dir/depend
