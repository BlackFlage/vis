# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

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

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.1.1\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual\cmake-build-debug"

# Include any dependencies generated for this target.
include ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\depend.make
# Include the progress variables for this target.
include ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\progress.make

# Include the compile flags for this target's objects.
include ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\flags.make

..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\__\__\src\visualinfo.c.obj: ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\flags.make
..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\__\__\src\visualinfo.c.obj: ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\includes_C.rsp
..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\__\__\src\visualinfo.c.obj: ..\components\vendor\glew\src\visualinfo.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object ../components/vendor/glew/build/cmake/CMakeFiles/visualinfo.dir/__/__/src/visualinfo.c.obj"
	cd C:\Users\BLACKF~1\ONEDRI~1\C__~1\visual\COMPON~1\vendor\glew\build\cmake
	C:\PROGRA~1\LLVM\bin\clang.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\visualinfo.dir\__\__\src\visualinfo.c.obj -c "C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual\components\vendor\glew\src\visualinfo.c"
	cd C:\Users\BLACKF~1\ONEDRI~1\C__~1\visual\CMAKE-~1

..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\__\__\src\visualinfo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/visualinfo.dir/__/__/src/visualinfo.c.i"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_C_CREATE_PREPROCESSED_SOURCE

..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\__\__\src\visualinfo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/visualinfo.dir/__/__/src/visualinfo.c.s"
	$(CMAKE_COMMAND) -E cmake_unimplemented_variable CMAKE_C_CREATE_ASSEMBLY_SOURCE

..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\__\visualinfo.rc.res: ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\flags.make
..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\__\visualinfo.rc.res: ..\components\vendor\glew\build\visualinfo.rc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building RC object ../components/vendor/glew/build/cmake/CMakeFiles/visualinfo.dir/__/visualinfo.rc.res"
	cd C:\Users\BLACKF~1\ONEDRI~1\C__~1\visual\COMPON~1\vendor\glew\build\cmake
	C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x64\rc.exe $(RC_DEFINES) $(RC_INCLUDES) $(RC_FLAGS) /fo CMakeFiles\visualinfo.dir\__\visualinfo.rc.res "C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual\components\vendor\glew\build\visualinfo.rc"
	cd C:\Users\BLACKF~1\ONEDRI~1\C__~1\visual\CMAKE-~1

# Object files for target visualinfo
visualinfo_OBJECTS = \
"CMakeFiles\visualinfo.dir\__\__\src\visualinfo.c.obj" \
"CMakeFiles\visualinfo.dir\__\visualinfo.rc.res"

# External object files for target visualinfo
visualinfo_EXTERNAL_OBJECTS =

bin\visualinfo.exe: ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\__\__\src\visualinfo.c.obj
bin\visualinfo.exe: ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\__\visualinfo.rc.res
bin\visualinfo.exe: ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\build.make
bin\visualinfo.exe: lib\glew32d.lib
bin\visualinfo.exe: ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\linklibs.rsp
bin\visualinfo.exe: ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable ..\..\..\..\..\cmake-build-debug\bin\visualinfo.exe"
	cd C:\Users\BLACKF~1\ONEDRI~1\C__~1\visual\COMPON~1\vendor\glew\build\cmake
	C:\PROGRA~1\LLVM\bin\clang.exe -fuse-ld=lld-link -nostartfiles -nostdlib -g -Xclang -gcodeview -O0 -D_DEBUG -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd -Xlinker /subsystem:console @CMakeFiles\visualinfo.dir\objects1.rsp -o ..\..\..\..\..\cmake-build-debug\bin\visualinfo.exe -Xlinker /implib:..\..\..\..\..\cmake-build-debug\lib\visualinfo.lib -Xlinker /pdb:"C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual\cmake-build-debug\bin\visualinfo.pdb" -Xlinker /version:0.0  @CMakeFiles\visualinfo.dir\linklibs.rsp
	cd C:\Users\BLACKF~1\ONEDRI~1\C__~1\visual\CMAKE-~1

# Rule to build all files generated by this target.
..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\build: bin\visualinfo.exe
.PHONY : ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\build

..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\clean:
	cd C:\Users\BLACKF~1\ONEDRI~1\C__~1\visual\COMPON~1\vendor\glew\build\cmake
	$(CMAKE_COMMAND) -P CMakeFiles\visualinfo.dir\cmake_clean.cmake
	cd C:\Users\BLACKF~1\ONEDRI~1\C__~1\visual\CMAKE-~1
.PHONY : ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\clean

..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual" "C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual\components\vendor\glew\build\cmake" "C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual\cmake-build-debug" "C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual\components\vendor\glew\build\cmake" "C:\Users\BlackFlage\OneDrive - Politechnika Wroclawska\C++\visual\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : ..\components\vendor\glew\build\cmake\CMakeFiles\visualinfo.dir\depend
