# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.23

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2022.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2022.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Misc\CNetworkProtocol\clientv20221004

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Misc\CNetworkProtocol\clientv20221004\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/v20221004.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/v20221004.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/v20221004.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/v20221004.dir/flags.make

CMakeFiles/v20221004.dir/src/main.c.obj: CMakeFiles/v20221004.dir/flags.make
CMakeFiles/v20221004.dir/src/main.c.obj: CMakeFiles/v20221004.dir/includes_C.rsp
CMakeFiles/v20221004.dir/src/main.c.obj: ../src/main.c
CMakeFiles/v20221004.dir/src/main.c.obj: CMakeFiles/v20221004.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Misc\CNetworkProtocol\clientv20221004\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/v20221004.dir/src/main.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/v20221004.dir/src/main.c.obj -MF CMakeFiles\v20221004.dir\src\main.c.obj.d -o CMakeFiles\v20221004.dir\src\main.c.obj -c D:\Misc\CNetworkProtocol\clientv20221004\src\main.c

CMakeFiles/v20221004.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/v20221004.dir/src/main.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Misc\CNetworkProtocol\clientv20221004\src\main.c > CMakeFiles\v20221004.dir\src\main.c.i

CMakeFiles/v20221004.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/v20221004.dir/src/main.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Misc\CNetworkProtocol\clientv20221004\src\main.c -o CMakeFiles\v20221004.dir\src\main.c.s

CMakeFiles/v20221004.dir/src/fileProcessor.c.obj: CMakeFiles/v20221004.dir/flags.make
CMakeFiles/v20221004.dir/src/fileProcessor.c.obj: CMakeFiles/v20221004.dir/includes_C.rsp
CMakeFiles/v20221004.dir/src/fileProcessor.c.obj: ../src/fileProcessor.c
CMakeFiles/v20221004.dir/src/fileProcessor.c.obj: CMakeFiles/v20221004.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Misc\CNetworkProtocol\clientv20221004\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/v20221004.dir/src/fileProcessor.c.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/v20221004.dir/src/fileProcessor.c.obj -MF CMakeFiles\v20221004.dir\src\fileProcessor.c.obj.d -o CMakeFiles\v20221004.dir\src\fileProcessor.c.obj -c D:\Misc\CNetworkProtocol\clientv20221004\src\fileProcessor.c

CMakeFiles/v20221004.dir/src/fileProcessor.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/v20221004.dir/src/fileProcessor.c.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E D:\Misc\CNetworkProtocol\clientv20221004\src\fileProcessor.c > CMakeFiles\v20221004.dir\src\fileProcessor.c.i

CMakeFiles/v20221004.dir/src/fileProcessor.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/v20221004.dir/src/fileProcessor.c.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S D:\Misc\CNetworkProtocol\clientv20221004\src\fileProcessor.c -o CMakeFiles\v20221004.dir\src\fileProcessor.c.s

# Object files for target v20221004
v20221004_OBJECTS = \
"CMakeFiles/v20221004.dir/src/main.c.obj" \
"CMakeFiles/v20221004.dir/src/fileProcessor.c.obj"

# External object files for target v20221004
v20221004_EXTERNAL_OBJECTS =

v20221004.exe: CMakeFiles/v20221004.dir/src/main.c.obj
v20221004.exe: CMakeFiles/v20221004.dir/src/fileProcessor.c.obj
v20221004.exe: CMakeFiles/v20221004.dir/build.make
v20221004.exe: CMakeFiles/v20221004.dir/linklibs.rsp
v20221004.exe: CMakeFiles/v20221004.dir/objects1.rsp
v20221004.exe: CMakeFiles/v20221004.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Misc\CNetworkProtocol\clientv20221004\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable v20221004.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\v20221004.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/v20221004.dir/build: v20221004.exe
.PHONY : CMakeFiles/v20221004.dir/build

CMakeFiles/v20221004.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\v20221004.dir\cmake_clean.cmake
.PHONY : CMakeFiles/v20221004.dir/clean

CMakeFiles/v20221004.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Misc\CNetworkProtocol\clientv20221004 D:\Misc\CNetworkProtocol\clientv20221004 D:\Misc\CNetworkProtocol\clientv20221004\cmake-build-debug D:\Misc\CNetworkProtocol\clientv20221004\cmake-build-debug D:\Misc\CNetworkProtocol\clientv20221004\cmake-build-debug\CMakeFiles\v20221004.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/v20221004.dir/depend
