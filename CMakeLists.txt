# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté shell
project(binsh)

set(CMAKE_C_FLAGS "-std=c99 -D_XOPEN_SOURCE=600 -Wl,--no-as-needed -ldl -pthread -lm")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )

# Crée des variables avec les fichiers à compiler
file(GLOB SRC
    "src/*.c"
    "src/commands/*.c"
)
file(GLOB HEADER
    "include/*.h"
    "include/commands/*.h"
)
# On indique que l'on veut un exécutable "shell" compilé à partir des fichiers décrits par les variables SRCS et HEADERS
add_executable(shell ${SRC} ${HEADER})


# building command executables

# ls
file(GLOB SRC_LS
    "src/commands/ls.c"
    "src/utils.c"
    "src/main/ls.c"
)
file(GLOB HEADER_LS
    "include/commands/ls.h"
)
add_executable(ls ${SRC_LS} ${HEADER_LS})
add_library(ls_lib SHARED ${SRC_LS})
set_target_properties(ls_lib PROPERTIES OUTPUT_NAME "ls")

# cd
file(GLOB SRC_CD
    "src/commands/cd.c"
    "src/main/cd.c"
)
file(GLOB HEADER_CD
    "include/commands/cd.h"
)
add_executable(cd ${SRC_CD} ${HEADER_CD})


# cat
file(GLOB SRC_CAT
    "src/commands/cat.c"
    "src/utils.c"
    "src/main/cat.c"
)
file(GLOB HEADER_CAT
    "include/commands/cat.h"
)
add_executable(cat ${SRC_CAT} ${HEADER_CAT})
add_library(cat_lib SHARED ${SRC_CAT})
set_target_properties(cat_lib PROPERTIES OUTPUT_NAME "cat")

# echo
file(GLOB SRC_ECHO
    "src/commands/echo.c"
    "src/utils.c"
    "src/main/echo.c"
)
file(GLOB HEADER_ECHO
    "include/commands/echo.h"
)
add_executable(echo ${SRC_ECHO} ${HEADER_ECHO})
add_library(echo_lib SHARED ${SRC_ECHO})
set_target_properties(echo_lib PROPERTIES OUTPUT_NAME "echo")


# mv
file(GLOB SRC_MV
    "src/commands/mv.c"
    "src/utils.c"
    "src/main/mv.c"
)
file(GLOB HEADER_MV
    "include/commands/mv.h"
)
add_executable(mv ${SRC_MV} ${HEADER_MV})
add_library(mv_lib SHARED ${SRC_MV})
set_target_properties(mv_lib PROPERTIES OUTPUT_NAME "mv")

# pwd
file(GLOB SRC_PWD
    "src/commands/pwd.c"
    "src/utils.c"
    "src/main/pwd.c"
)
file(GLOB HEADER_PWD
    "include/commands/pwd.h"
)
add_executable(pwd ${SRC_PWD} ${HEADER_PWD})
add_library(pwd_lib SHARED ${SRC_PWD})
set_target_properties(pwd_lib PROPERTIES OUTPUT_NAME "pwd")

# mkdir
file(GLOB SRC_MKDIR
    "src/commands/mkdir.c"
    "src/utils.c"
    "src/main/mkdir.c"
)
file(GLOB HEADER_MKDIR
    "include/commands/mkdir.h"
)
add_executable(mkdir ${SRC_MKDIR} ${HEADER_MKDIR})
add_library(mkdir_lib SHARED ${SRC_MKDIR})
set_target_properties(mkdir_lib PROPERTIES OUTPUT_NAME "mkdir")

# connect
file(GLOB SRC_CONNECT
    "src/commands/connect.c"
    "src/utils.c"
    "src/main/connect.c"
)
file(GLOB HEADER_CONNECT
    "include/commands/connect.h"
)
add_executable(connect ${SRC_CONNECT} ${HEADER_CONNECT})
add_library(connect_lib SHARED ${SRC_CONNECT})
set_target_properties(connect_lib PROPERTIES OUTPUT_NAME "connect")

# du
file(GLOB SRC_DU
    "src/commands/du.c"
    "src/utils.c"
    "src/main/du.c"
)
file(GLOB HEADER_DU
    "include/commands/du.h"
)
add_executable(du ${SRC_DU} ${HEADER_DU})
add_library(du_lib SHARED ${SRC_DU})
set_target_properties(du_lib PROPERTIES OUTPUT_NAME "du")

# rm
file(GLOB SRC_RM
    "src/commands/rm.c"
    "src/utils.c"
    "src/main/rm.c"
)
file(GLOB HEADER_RM
    "include/commands/rm.h"
)
add_executable(rm ${SRC_RM} ${HEADER_RM})
add_library(rm_lib SHARED ${SRC_RM})
set_target_properties(rm_lib PROPERTIES OUTPUT_NAME "rm")

# cp
file(GLOB SRC_CP
    "src/commands/cp.c"
    "src/utils.c"
    "src/main/cp.c"
)
file(GLOB HEADER_CP
    "include/commands/cp.h"
)
add_executable(cp ${SRC_CP} ${HEADER_CP})
add_library(cp_lib SHARED ${SRC_CP})
set_target_properties(cp_lib PROPERTIES OUTPUT_NAME "cp")

# chmod
file(GLOB SRC_CHMOD
    "src/commands/chmod.c"
    "src/utils.c"
    "src/main/chmod.c"
)
file(GLOB HEADER_CHMOD
    "include/commands/chmod.h"
)
add_executable(chmod ${SRC_CHMOD} ${HEADER_CHMOD})
add_library(chmod_lib SHARED ${SRC_CHMOD})
set_target_properties(chmod_lib PROPERTIES OUTPUT_NAME "chmod")


# chown
file(GLOB SRC_CHOWN
    "src/commands/chown.c"
    "src/utils.c"
    "src/main/chown.c"
)
file(GLOB HEADER_CHOWN
    "include/commands/chown.h"
)
add_executable(chown ${SRC_CHOWN} ${HEADER_CHOWN})
add_library(chown_lib SHARED ${SRC_CHOWN})
set_target_properties(chown_lib PROPERTIES OUTPUT_NAME "chown")
