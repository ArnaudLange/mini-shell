# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_SOURCE_DIR = /home/antoine/Workspace/c/Shell

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/antoine/Workspace/c/Shell

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/antoine/Workspace/c/Shell/CMakeFiles /home/antoine/Workspace/c/Shell/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/antoine/Workspace/c/Shell/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named echo_lib

# Build rule for target.
echo_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 echo_lib
.PHONY : echo_lib

# fast build rule for target.
echo_lib/fast:
	$(MAKE) -f CMakeFiles/echo_lib.dir/build.make CMakeFiles/echo_lib.dir/build
.PHONY : echo_lib/fast

#=============================================================================
# Target rules for targets named echo

# Build rule for target.
echo: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 echo
.PHONY : echo

# fast build rule for target.
echo/fast:
	$(MAKE) -f CMakeFiles/echo.dir/build.make CMakeFiles/echo.dir/build
.PHONY : echo/fast

#=============================================================================
# Target rules for targets named cat_lib

# Build rule for target.
cat_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cat_lib
.PHONY : cat_lib

# fast build rule for target.
cat_lib/fast:
	$(MAKE) -f CMakeFiles/cat_lib.dir/build.make CMakeFiles/cat_lib.dir/build
.PHONY : cat_lib/fast

#=============================================================================
# Target rules for targets named cat

# Build rule for target.
cat: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cat
.PHONY : cat

# fast build rule for target.
cat/fast:
	$(MAKE) -f CMakeFiles/cat.dir/build.make CMakeFiles/cat.dir/build
.PHONY : cat/fast

#=============================================================================
# Target rules for targets named shell

# Build rule for target.
shell: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 shell
.PHONY : shell

# fast build rule for target.
shell/fast:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/build
.PHONY : shell/fast

#=============================================================================
# Target rules for targets named ls

# Build rule for target.
ls: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ls
.PHONY : ls

# fast build rule for target.
ls/fast:
	$(MAKE) -f CMakeFiles/ls.dir/build.make CMakeFiles/ls.dir/build
.PHONY : ls/fast

#=============================================================================
# Target rules for targets named ls_lib

# Build rule for target.
ls_lib: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 ls_lib
.PHONY : ls_lib

# fast build rule for target.
ls_lib/fast:
	$(MAKE) -f CMakeFiles/ls_lib.dir/build.make CMakeFiles/ls_lib.dir/build
.PHONY : ls_lib/fast

#=============================================================================
# Target rules for targets named cd

# Build rule for target.
cd: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 cd
.PHONY : cd

# fast build rule for target.
cd/fast:
	$(MAKE) -f CMakeFiles/cd.dir/build.make CMakeFiles/cd.dir/build
.PHONY : cd/fast

src/commands.o: src/commands.c.o

.PHONY : src/commands.o

# target to build an object file
src/commands.c.o:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands.c.o
.PHONY : src/commands.c.o

src/commands.i: src/commands.c.i

.PHONY : src/commands.i

# target to preprocess a source file
src/commands.c.i:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands.c.i
.PHONY : src/commands.c.i

src/commands.s: src/commands.c.s

.PHONY : src/commands.s

# target to generate assembly for a file
src/commands.c.s:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands.c.s
.PHONY : src/commands.c.s

src/commands/cat.o: src/commands/cat.c.o

.PHONY : src/commands/cat.o

# target to build an object file
src/commands/cat.c.o:
	$(MAKE) -f CMakeFiles/cat_lib.dir/build.make CMakeFiles/cat_lib.dir/src/commands/cat.c.o
	$(MAKE) -f CMakeFiles/cat.dir/build.make CMakeFiles/cat.dir/src/commands/cat.c.o
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands/cat.c.o
.PHONY : src/commands/cat.c.o

src/commands/cat.i: src/commands/cat.c.i

.PHONY : src/commands/cat.i

# target to preprocess a source file
src/commands/cat.c.i:
	$(MAKE) -f CMakeFiles/cat_lib.dir/build.make CMakeFiles/cat_lib.dir/src/commands/cat.c.i
	$(MAKE) -f CMakeFiles/cat.dir/build.make CMakeFiles/cat.dir/src/commands/cat.c.i
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands/cat.c.i
.PHONY : src/commands/cat.c.i

src/commands/cat.s: src/commands/cat.c.s

.PHONY : src/commands/cat.s

# target to generate assembly for a file
src/commands/cat.c.s:
	$(MAKE) -f CMakeFiles/cat_lib.dir/build.make CMakeFiles/cat_lib.dir/src/commands/cat.c.s
	$(MAKE) -f CMakeFiles/cat.dir/build.make CMakeFiles/cat.dir/src/commands/cat.c.s
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands/cat.c.s
.PHONY : src/commands/cat.c.s

src/commands/cd.o: src/commands/cd.c.o

.PHONY : src/commands/cd.o

# target to build an object file
src/commands/cd.c.o:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands/cd.c.o
	$(MAKE) -f CMakeFiles/cd.dir/build.make CMakeFiles/cd.dir/src/commands/cd.c.o
.PHONY : src/commands/cd.c.o

src/commands/cd.i: src/commands/cd.c.i

.PHONY : src/commands/cd.i

# target to preprocess a source file
src/commands/cd.c.i:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands/cd.c.i
	$(MAKE) -f CMakeFiles/cd.dir/build.make CMakeFiles/cd.dir/src/commands/cd.c.i
.PHONY : src/commands/cd.c.i

src/commands/cd.s: src/commands/cd.c.s

.PHONY : src/commands/cd.s

# target to generate assembly for a file
src/commands/cd.c.s:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands/cd.c.s
	$(MAKE) -f CMakeFiles/cd.dir/build.make CMakeFiles/cd.dir/src/commands/cd.c.s
.PHONY : src/commands/cd.c.s

src/commands/echo.o: src/commands/echo.c.o

.PHONY : src/commands/echo.o

# target to build an object file
src/commands/echo.c.o:
	$(MAKE) -f CMakeFiles/echo_lib.dir/build.make CMakeFiles/echo_lib.dir/src/commands/echo.c.o
	$(MAKE) -f CMakeFiles/echo.dir/build.make CMakeFiles/echo.dir/src/commands/echo.c.o
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands/echo.c.o
.PHONY : src/commands/echo.c.o

src/commands/echo.i: src/commands/echo.c.i

.PHONY : src/commands/echo.i

# target to preprocess a source file
src/commands/echo.c.i:
	$(MAKE) -f CMakeFiles/echo_lib.dir/build.make CMakeFiles/echo_lib.dir/src/commands/echo.c.i
	$(MAKE) -f CMakeFiles/echo.dir/build.make CMakeFiles/echo.dir/src/commands/echo.c.i
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands/echo.c.i
.PHONY : src/commands/echo.c.i

src/commands/echo.s: src/commands/echo.c.s

.PHONY : src/commands/echo.s

# target to generate assembly for a file
src/commands/echo.c.s:
	$(MAKE) -f CMakeFiles/echo_lib.dir/build.make CMakeFiles/echo_lib.dir/src/commands/echo.c.s
	$(MAKE) -f CMakeFiles/echo.dir/build.make CMakeFiles/echo.dir/src/commands/echo.c.s
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands/echo.c.s
.PHONY : src/commands/echo.c.s

src/commands/ls.o: src/commands/ls.c.o

.PHONY : src/commands/ls.o

# target to build an object file
src/commands/ls.c.o:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands/ls.c.o
	$(MAKE) -f CMakeFiles/ls.dir/build.make CMakeFiles/ls.dir/src/commands/ls.c.o
	$(MAKE) -f CMakeFiles/ls_lib.dir/build.make CMakeFiles/ls_lib.dir/src/commands/ls.c.o
.PHONY : src/commands/ls.c.o

src/commands/ls.i: src/commands/ls.c.i

.PHONY : src/commands/ls.i

# target to preprocess a source file
src/commands/ls.c.i:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands/ls.c.i
	$(MAKE) -f CMakeFiles/ls.dir/build.make CMakeFiles/ls.dir/src/commands/ls.c.i
	$(MAKE) -f CMakeFiles/ls_lib.dir/build.make CMakeFiles/ls_lib.dir/src/commands/ls.c.i
.PHONY : src/commands/ls.c.i

src/commands/ls.s: src/commands/ls.c.s

.PHONY : src/commands/ls.s

# target to generate assembly for a file
src/commands/ls.c.s:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/commands/ls.c.s
	$(MAKE) -f CMakeFiles/ls.dir/build.make CMakeFiles/ls.dir/src/commands/ls.c.s
	$(MAKE) -f CMakeFiles/ls_lib.dir/build.make CMakeFiles/ls_lib.dir/src/commands/ls.c.s
.PHONY : src/commands/ls.c.s

src/main.o: src/main.c.o

.PHONY : src/main.o

# target to build an object file
src/main.c.o:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/main.c.o
.PHONY : src/main.c.o

src/main.i: src/main.c.i

.PHONY : src/main.i

# target to preprocess a source file
src/main.c.i:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/main.c.i
.PHONY : src/main.c.i

src/main.s: src/main.c.s

.PHONY : src/main.s

# target to generate assembly for a file
src/main.c.s:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/main.c.s
.PHONY : src/main.c.s

src/main/cat.o: src/main/cat.c.o

.PHONY : src/main/cat.o

# target to build an object file
src/main/cat.c.o:
	$(MAKE) -f CMakeFiles/cat_lib.dir/build.make CMakeFiles/cat_lib.dir/src/main/cat.c.o
	$(MAKE) -f CMakeFiles/cat.dir/build.make CMakeFiles/cat.dir/src/main/cat.c.o
.PHONY : src/main/cat.c.o

src/main/cat.i: src/main/cat.c.i

.PHONY : src/main/cat.i

# target to preprocess a source file
src/main/cat.c.i:
	$(MAKE) -f CMakeFiles/cat_lib.dir/build.make CMakeFiles/cat_lib.dir/src/main/cat.c.i
	$(MAKE) -f CMakeFiles/cat.dir/build.make CMakeFiles/cat.dir/src/main/cat.c.i
.PHONY : src/main/cat.c.i

src/main/cat.s: src/main/cat.c.s

.PHONY : src/main/cat.s

# target to generate assembly for a file
src/main/cat.c.s:
	$(MAKE) -f CMakeFiles/cat_lib.dir/build.make CMakeFiles/cat_lib.dir/src/main/cat.c.s
	$(MAKE) -f CMakeFiles/cat.dir/build.make CMakeFiles/cat.dir/src/main/cat.c.s
.PHONY : src/main/cat.c.s

src/main/cd.o: src/main/cd.c.o

.PHONY : src/main/cd.o

# target to build an object file
src/main/cd.c.o:
	$(MAKE) -f CMakeFiles/cd.dir/build.make CMakeFiles/cd.dir/src/main/cd.c.o
.PHONY : src/main/cd.c.o

src/main/cd.i: src/main/cd.c.i

.PHONY : src/main/cd.i

# target to preprocess a source file
src/main/cd.c.i:
	$(MAKE) -f CMakeFiles/cd.dir/build.make CMakeFiles/cd.dir/src/main/cd.c.i
.PHONY : src/main/cd.c.i

src/main/cd.s: src/main/cd.c.s

.PHONY : src/main/cd.s

# target to generate assembly for a file
src/main/cd.c.s:
	$(MAKE) -f CMakeFiles/cd.dir/build.make CMakeFiles/cd.dir/src/main/cd.c.s
.PHONY : src/main/cd.c.s

src/main/echo.o: src/main/echo.c.o

.PHONY : src/main/echo.o

# target to build an object file
src/main/echo.c.o:
	$(MAKE) -f CMakeFiles/echo_lib.dir/build.make CMakeFiles/echo_lib.dir/src/main/echo.c.o
	$(MAKE) -f CMakeFiles/echo.dir/build.make CMakeFiles/echo.dir/src/main/echo.c.o
.PHONY : src/main/echo.c.o

src/main/echo.i: src/main/echo.c.i

.PHONY : src/main/echo.i

# target to preprocess a source file
src/main/echo.c.i:
	$(MAKE) -f CMakeFiles/echo_lib.dir/build.make CMakeFiles/echo_lib.dir/src/main/echo.c.i
	$(MAKE) -f CMakeFiles/echo.dir/build.make CMakeFiles/echo.dir/src/main/echo.c.i
.PHONY : src/main/echo.c.i

src/main/echo.s: src/main/echo.c.s

.PHONY : src/main/echo.s

# target to generate assembly for a file
src/main/echo.c.s:
	$(MAKE) -f CMakeFiles/echo_lib.dir/build.make CMakeFiles/echo_lib.dir/src/main/echo.c.s
	$(MAKE) -f CMakeFiles/echo.dir/build.make CMakeFiles/echo.dir/src/main/echo.c.s
.PHONY : src/main/echo.c.s

src/main/ls.o: src/main/ls.c.o

.PHONY : src/main/ls.o

# target to build an object file
src/main/ls.c.o:
	$(MAKE) -f CMakeFiles/ls.dir/build.make CMakeFiles/ls.dir/src/main/ls.c.o
	$(MAKE) -f CMakeFiles/ls_lib.dir/build.make CMakeFiles/ls_lib.dir/src/main/ls.c.o
.PHONY : src/main/ls.c.o

src/main/ls.i: src/main/ls.c.i

.PHONY : src/main/ls.i

# target to preprocess a source file
src/main/ls.c.i:
	$(MAKE) -f CMakeFiles/ls.dir/build.make CMakeFiles/ls.dir/src/main/ls.c.i
	$(MAKE) -f CMakeFiles/ls_lib.dir/build.make CMakeFiles/ls_lib.dir/src/main/ls.c.i
.PHONY : src/main/ls.c.i

src/main/ls.s: src/main/ls.c.s

.PHONY : src/main/ls.s

# target to generate assembly for a file
src/main/ls.c.s:
	$(MAKE) -f CMakeFiles/ls.dir/build.make CMakeFiles/ls.dir/src/main/ls.c.s
	$(MAKE) -f CMakeFiles/ls_lib.dir/build.make CMakeFiles/ls_lib.dir/src/main/ls.c.s
.PHONY : src/main/ls.c.s

src/process.o: src/process.c.o

.PHONY : src/process.o

# target to build an object file
src/process.c.o:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/process.c.o
.PHONY : src/process.c.o

src/process.i: src/process.c.i

.PHONY : src/process.i

# target to preprocess a source file
src/process.c.i:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/process.c.i
.PHONY : src/process.c.i

src/process.s: src/process.c.s

.PHONY : src/process.s

# target to generate assembly for a file
src/process.c.s:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/process.c.s
.PHONY : src/process.c.s

src/redirection.o: src/redirection.c.o

.PHONY : src/redirection.o

# target to build an object file
src/redirection.c.o:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/redirection.c.o
.PHONY : src/redirection.c.o

src/redirection.i: src/redirection.c.i

.PHONY : src/redirection.i

# target to preprocess a source file
src/redirection.c.i:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/redirection.c.i
.PHONY : src/redirection.c.i

src/redirection.s: src/redirection.c.s

.PHONY : src/redirection.s

# target to generate assembly for a file
src/redirection.c.s:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/redirection.c.s
.PHONY : src/redirection.c.s

src/shell.o: src/shell.c.o

.PHONY : src/shell.o

# target to build an object file
src/shell.c.o:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/shell.c.o
.PHONY : src/shell.c.o

src/shell.i: src/shell.c.i

.PHONY : src/shell.i

# target to preprocess a source file
src/shell.c.i:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/shell.c.i
.PHONY : src/shell.c.i

src/shell.s: src/shell.c.s

.PHONY : src/shell.s

# target to generate assembly for a file
src/shell.c.s:
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/shell.c.s
.PHONY : src/shell.c.s

src/utils.o: src/utils.c.o

.PHONY : src/utils.o

# target to build an object file
src/utils.c.o:
	$(MAKE) -f CMakeFiles/echo_lib.dir/build.make CMakeFiles/echo_lib.dir/src/utils.c.o
	$(MAKE) -f CMakeFiles/echo.dir/build.make CMakeFiles/echo.dir/src/utils.c.o
	$(MAKE) -f CMakeFiles/cat_lib.dir/build.make CMakeFiles/cat_lib.dir/src/utils.c.o
	$(MAKE) -f CMakeFiles/cat.dir/build.make CMakeFiles/cat.dir/src/utils.c.o
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/utils.c.o
	$(MAKE) -f CMakeFiles/ls.dir/build.make CMakeFiles/ls.dir/src/utils.c.o
	$(MAKE) -f CMakeFiles/ls_lib.dir/build.make CMakeFiles/ls_lib.dir/src/utils.c.o
.PHONY : src/utils.c.o

src/utils.i: src/utils.c.i

.PHONY : src/utils.i

# target to preprocess a source file
src/utils.c.i:
	$(MAKE) -f CMakeFiles/echo_lib.dir/build.make CMakeFiles/echo_lib.dir/src/utils.c.i
	$(MAKE) -f CMakeFiles/echo.dir/build.make CMakeFiles/echo.dir/src/utils.c.i
	$(MAKE) -f CMakeFiles/cat_lib.dir/build.make CMakeFiles/cat_lib.dir/src/utils.c.i
	$(MAKE) -f CMakeFiles/cat.dir/build.make CMakeFiles/cat.dir/src/utils.c.i
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/utils.c.i
	$(MAKE) -f CMakeFiles/ls.dir/build.make CMakeFiles/ls.dir/src/utils.c.i
	$(MAKE) -f CMakeFiles/ls_lib.dir/build.make CMakeFiles/ls_lib.dir/src/utils.c.i
.PHONY : src/utils.c.i

src/utils.s: src/utils.c.s

.PHONY : src/utils.s

# target to generate assembly for a file
src/utils.c.s:
	$(MAKE) -f CMakeFiles/echo_lib.dir/build.make CMakeFiles/echo_lib.dir/src/utils.c.s
	$(MAKE) -f CMakeFiles/echo.dir/build.make CMakeFiles/echo.dir/src/utils.c.s
	$(MAKE) -f CMakeFiles/cat_lib.dir/build.make CMakeFiles/cat_lib.dir/src/utils.c.s
	$(MAKE) -f CMakeFiles/cat.dir/build.make CMakeFiles/cat.dir/src/utils.c.s
	$(MAKE) -f CMakeFiles/shell.dir/build.make CMakeFiles/shell.dir/src/utils.c.s
	$(MAKE) -f CMakeFiles/ls.dir/build.make CMakeFiles/ls.dir/src/utils.c.s
	$(MAKE) -f CMakeFiles/ls_lib.dir/build.make CMakeFiles/ls_lib.dir/src/utils.c.s
.PHONY : src/utils.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... echo_lib"
	@echo "... echo"
	@echo "... cat_lib"
	@echo "... cat"
	@echo "... rebuild_cache"
	@echo "... shell"
	@echo "... ls"
	@echo "... ls_lib"
	@echo "... cd"
	@echo "... src/commands.o"
	@echo "... src/commands.i"
	@echo "... src/commands.s"
	@echo "... src/commands/cat.o"
	@echo "... src/commands/cat.i"
	@echo "... src/commands/cat.s"
	@echo "... src/commands/cd.o"
	@echo "... src/commands/cd.i"
	@echo "... src/commands/cd.s"
	@echo "... src/commands/echo.o"
	@echo "... src/commands/echo.i"
	@echo "... src/commands/echo.s"
	@echo "... src/commands/ls.o"
	@echo "... src/commands/ls.i"
	@echo "... src/commands/ls.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
	@echo "... src/main/cat.o"
	@echo "... src/main/cat.i"
	@echo "... src/main/cat.s"
	@echo "... src/main/cd.o"
	@echo "... src/main/cd.i"
	@echo "... src/main/cd.s"
	@echo "... src/main/echo.o"
	@echo "... src/main/echo.i"
	@echo "... src/main/echo.s"
	@echo "... src/main/ls.o"
	@echo "... src/main/ls.i"
	@echo "... src/main/ls.s"
	@echo "... src/process.o"
	@echo "... src/process.i"
	@echo "... src/process.s"
	@echo "... src/redirection.o"
	@echo "... src/redirection.i"
	@echo "... src/redirection.s"
	@echo "... src/shell.o"
	@echo "... src/shell.i"
	@echo "... src/shell.s"
	@echo "... src/utils.o"
	@echo "... src/utils.i"
	@echo "... src/utils.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

