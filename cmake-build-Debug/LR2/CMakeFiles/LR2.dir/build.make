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
CMAKE_SOURCE_DIR = C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\LR2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\LR2

# Include any dependencies generated for this target.
include CMakeFiles/LR2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/LR2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/LR2.dir/flags.make

CMakeFiles/LR2.dir/main.cpp.obj: CMakeFiles/LR2.dir/flags.make
CMakeFiles/LR2.dir/main.cpp.obj: C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/LR2/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\LR2\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/LR2.dir/main.cpp.obj"
	C:\TDM-GCC-64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -g -O0 -Wall -o CMakeFiles\LR2.dir\main.cpp.obj -c C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\LR2\main.cpp

CMakeFiles/LR2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LR2.dir/main.cpp.i"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -g -O0 -Wall -E C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\LR2\main.cpp > CMakeFiles\LR2.dir\main.cpp.i

CMakeFiles/LR2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LR2.dir/main.cpp.s"
	C:\TDM-GCC-64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS)  -g -O0 -Wall -S C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\LR2\main.cpp -o CMakeFiles\LR2.dir\main.cpp.s

# Object files for target LR2
LR2_OBJECTS = \
"CMakeFiles/LR2.dir/main.cpp.obj"

# External object files for target LR2
LR2_EXTERNAL_OBJECTS =

C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR2.exe: CMakeFiles/LR2.dir/main.cpp.obj
C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR2.exe: CMakeFiles/LR2.dir/build.make
C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR2.exe: CMakeFiles/LR2.dir/linklibs.rsp
C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR2.exe: CMakeFiles/LR2.dir/objects1.rsp
C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR2.exe: CMakeFiles/LR2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\LR2\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\output\LR2.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LR2.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/LR2.dir/build: C:/Users/FLARTY/Desktop/Programs/Semester_4/AaDS/cmake-build-Debug/output/LR2.exe

.PHONY : CMakeFiles/LR2.dir/build

CMakeFiles/LR2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\LR2.dir\cmake_clean.cmake
.PHONY : CMakeFiles/LR2.dir/clean

CMakeFiles/LR2.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\LR2 C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\LR2 C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\LR2 C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\LR2 C:\Users\FLARTY\Desktop\Programs\Semester_4\AaDS\cmake-build-Debug\LR2\CMakeFiles\LR2.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/LR2.dir/depend

