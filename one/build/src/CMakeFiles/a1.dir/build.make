# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /media/linux/6.837/one

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/linux/6.837/one/build

# Include any dependencies generated for this target.
include src/CMakeFiles/a1.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/a1.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/a1.dir/flags.make

src/CMakeFiles/a1.dir/camera.cpp.o: src/CMakeFiles/a1.dir/flags.make
src/CMakeFiles/a1.dir/camera.cpp.o: ../src/camera.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /media/linux/6.837/one/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/a1.dir/camera.cpp.o"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/a1.dir/camera.cpp.o -c /media/linux/6.837/one/src/camera.cpp

src/CMakeFiles/a1.dir/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a1.dir/camera.cpp.i"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /media/linux/6.837/one/src/camera.cpp > CMakeFiles/a1.dir/camera.cpp.i

src/CMakeFiles/a1.dir/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a1.dir/camera.cpp.s"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /media/linux/6.837/one/src/camera.cpp -o CMakeFiles/a1.dir/camera.cpp.s

src/CMakeFiles/a1.dir/camera.cpp.o.requires:
.PHONY : src/CMakeFiles/a1.dir/camera.cpp.o.requires

src/CMakeFiles/a1.dir/camera.cpp.o.provides: src/CMakeFiles/a1.dir/camera.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/a1.dir/build.make src/CMakeFiles/a1.dir/camera.cpp.o.provides.build
.PHONY : src/CMakeFiles/a1.dir/camera.cpp.o.provides

src/CMakeFiles/a1.dir/camera.cpp.o.provides.build: src/CMakeFiles/a1.dir/camera.cpp.o

src/CMakeFiles/a1.dir/curve.cpp.o: src/CMakeFiles/a1.dir/flags.make
src/CMakeFiles/a1.dir/curve.cpp.o: ../src/curve.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /media/linux/6.837/one/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/a1.dir/curve.cpp.o"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/a1.dir/curve.cpp.o -c /media/linux/6.837/one/src/curve.cpp

src/CMakeFiles/a1.dir/curve.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a1.dir/curve.cpp.i"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /media/linux/6.837/one/src/curve.cpp > CMakeFiles/a1.dir/curve.cpp.i

src/CMakeFiles/a1.dir/curve.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a1.dir/curve.cpp.s"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /media/linux/6.837/one/src/curve.cpp -o CMakeFiles/a1.dir/curve.cpp.s

src/CMakeFiles/a1.dir/curve.cpp.o.requires:
.PHONY : src/CMakeFiles/a1.dir/curve.cpp.o.requires

src/CMakeFiles/a1.dir/curve.cpp.o.provides: src/CMakeFiles/a1.dir/curve.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/a1.dir/build.make src/CMakeFiles/a1.dir/curve.cpp.o.provides.build
.PHONY : src/CMakeFiles/a1.dir/curve.cpp.o.provides

src/CMakeFiles/a1.dir/curve.cpp.o.provides.build: src/CMakeFiles/a1.dir/curve.cpp.o

src/CMakeFiles/a1.dir/main.cpp.o: src/CMakeFiles/a1.dir/flags.make
src/CMakeFiles/a1.dir/main.cpp.o: ../src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /media/linux/6.837/one/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/a1.dir/main.cpp.o"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/a1.dir/main.cpp.o -c /media/linux/6.837/one/src/main.cpp

src/CMakeFiles/a1.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a1.dir/main.cpp.i"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /media/linux/6.837/one/src/main.cpp > CMakeFiles/a1.dir/main.cpp.i

src/CMakeFiles/a1.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a1.dir/main.cpp.s"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /media/linux/6.837/one/src/main.cpp -o CMakeFiles/a1.dir/main.cpp.s

src/CMakeFiles/a1.dir/main.cpp.o.requires:
.PHONY : src/CMakeFiles/a1.dir/main.cpp.o.requires

src/CMakeFiles/a1.dir/main.cpp.o.provides: src/CMakeFiles/a1.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/a1.dir/build.make src/CMakeFiles/a1.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/a1.dir/main.cpp.o.provides

src/CMakeFiles/a1.dir/main.cpp.o.provides.build: src/CMakeFiles/a1.dir/main.cpp.o

src/CMakeFiles/a1.dir/parse.cpp.o: src/CMakeFiles/a1.dir/flags.make
src/CMakeFiles/a1.dir/parse.cpp.o: ../src/parse.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /media/linux/6.837/one/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/a1.dir/parse.cpp.o"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/a1.dir/parse.cpp.o -c /media/linux/6.837/one/src/parse.cpp

src/CMakeFiles/a1.dir/parse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a1.dir/parse.cpp.i"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /media/linux/6.837/one/src/parse.cpp > CMakeFiles/a1.dir/parse.cpp.i

src/CMakeFiles/a1.dir/parse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a1.dir/parse.cpp.s"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /media/linux/6.837/one/src/parse.cpp -o CMakeFiles/a1.dir/parse.cpp.s

src/CMakeFiles/a1.dir/parse.cpp.o.requires:
.PHONY : src/CMakeFiles/a1.dir/parse.cpp.o.requires

src/CMakeFiles/a1.dir/parse.cpp.o.provides: src/CMakeFiles/a1.dir/parse.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/a1.dir/build.make src/CMakeFiles/a1.dir/parse.cpp.o.provides.build
.PHONY : src/CMakeFiles/a1.dir/parse.cpp.o.provides

src/CMakeFiles/a1.dir/parse.cpp.o.provides.build: src/CMakeFiles/a1.dir/parse.cpp.o

src/CMakeFiles/a1.dir/surf.cpp.o: src/CMakeFiles/a1.dir/flags.make
src/CMakeFiles/a1.dir/surf.cpp.o: ../src/surf.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /media/linux/6.837/one/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/CMakeFiles/a1.dir/surf.cpp.o"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/a1.dir/surf.cpp.o -c /media/linux/6.837/one/src/surf.cpp

src/CMakeFiles/a1.dir/surf.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a1.dir/surf.cpp.i"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /media/linux/6.837/one/src/surf.cpp > CMakeFiles/a1.dir/surf.cpp.i

src/CMakeFiles/a1.dir/surf.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a1.dir/surf.cpp.s"
	cd /media/linux/6.837/one/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /media/linux/6.837/one/src/surf.cpp -o CMakeFiles/a1.dir/surf.cpp.s

src/CMakeFiles/a1.dir/surf.cpp.o.requires:
.PHONY : src/CMakeFiles/a1.dir/surf.cpp.o.requires

src/CMakeFiles/a1.dir/surf.cpp.o.provides: src/CMakeFiles/a1.dir/surf.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/a1.dir/build.make src/CMakeFiles/a1.dir/surf.cpp.o.provides.build
.PHONY : src/CMakeFiles/a1.dir/surf.cpp.o.provides

src/CMakeFiles/a1.dir/surf.cpp.o.provides.build: src/CMakeFiles/a1.dir/surf.cpp.o

# Object files for target a1
a1_OBJECTS = \
"CMakeFiles/a1.dir/camera.cpp.o" \
"CMakeFiles/a1.dir/curve.cpp.o" \
"CMakeFiles/a1.dir/main.cpp.o" \
"CMakeFiles/a1.dir/parse.cpp.o" \
"CMakeFiles/a1.dir/surf.cpp.o"

# External object files for target a1
a1_EXTERNAL_OBJECTS =

src/a1: src/CMakeFiles/a1.dir/camera.cpp.o
src/a1: src/CMakeFiles/a1.dir/curve.cpp.o
src/a1: src/CMakeFiles/a1.dir/main.cpp.o
src/a1: src/CMakeFiles/a1.dir/parse.cpp.o
src/a1: src/CMakeFiles/a1.dir/surf.cpp.o
src/a1: src/CMakeFiles/a1.dir/build.make
src/a1: vecmath/libvecmath.a
src/a1: /usr/lib/x86_64-linux-gnu/libGLU.so
src/a1: /usr/lib/x86_64-linux-gnu/libGL.so
src/a1: /usr/lib/x86_64-linux-gnu/libSM.so
src/a1: /usr/lib/x86_64-linux-gnu/libICE.so
src/a1: /usr/lib/x86_64-linux-gnu/libX11.so
src/a1: /usr/lib/x86_64-linux-gnu/libXext.so
src/a1: /usr/lib/x86_64-linux-gnu/libglut.so
src/a1: /usr/lib/x86_64-linux-gnu/libXmu.so
src/a1: /usr/lib/x86_64-linux-gnu/libXi.so
src/a1: src/CMakeFiles/a1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable a1"
	cd /media/linux/6.837/one/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/a1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/a1.dir/build: src/a1
.PHONY : src/CMakeFiles/a1.dir/build

src/CMakeFiles/a1.dir/requires: src/CMakeFiles/a1.dir/camera.cpp.o.requires
src/CMakeFiles/a1.dir/requires: src/CMakeFiles/a1.dir/curve.cpp.o.requires
src/CMakeFiles/a1.dir/requires: src/CMakeFiles/a1.dir/main.cpp.o.requires
src/CMakeFiles/a1.dir/requires: src/CMakeFiles/a1.dir/parse.cpp.o.requires
src/CMakeFiles/a1.dir/requires: src/CMakeFiles/a1.dir/surf.cpp.o.requires
.PHONY : src/CMakeFiles/a1.dir/requires

src/CMakeFiles/a1.dir/clean:
	cd /media/linux/6.837/one/build/src && $(CMAKE_COMMAND) -P CMakeFiles/a1.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/a1.dir/clean

src/CMakeFiles/a1.dir/depend:
	cd /media/linux/6.837/one/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/linux/6.837/one /media/linux/6.837/one/src /media/linux/6.837/one/build /media/linux/6.837/one/build/src /media/linux/6.837/one/build/src/CMakeFiles/a1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/a1.dir/depend
