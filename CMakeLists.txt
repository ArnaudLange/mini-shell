# Nous voulons un cmake "récent" pour utiliser les dernières fonctionnalités
cmake_minimum_required(VERSION 3.0)

# Notre projet est étiqueté shell
project(binsh)

set(CMAKE_C_FLAGS "-std=c99 -D_XOPEN_SOURCE=600")
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

# building command libraries
add_library(lib SHARED ${SRC_LS})
set_target_properties(lib PROPERTIES OUTPUT_NAME "insh")