cmake_minimum_required(VERSION 3.4.3)
project(GANN)

set(GCC_COMPILE_FLAGS "-std=c++14 -Wall")
set(GCC_LINK_FLAGS "-std=c++14 -Wall")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COMPILE_FLAGS}")

include_directories(GANN)
include_directories(/usr/include)
file(GLOB SOURCES "GANN/*.cpp")

find_library(ALLEGRO_LIB NAMES allegro PATHS /usr/lib/ /usr/local/lib)
find_library(ALLEGRO_PRIMITIVES_LIB NAMES allegro_primitives PATHS /usr/lib/ /usr/local/lib)

if (ALLEGRO_LIB_NOTFOUND)
	MESSAGE(WARNING "Allegro library could not be found!")
else()
	MESSAGE(STATUS "Found: " ${ALLEGRO_LIB})
endif (ALLEGRO_LIB_NOTFOUND)

if (ALLEGRO_PRIMITIVES_LIB_NOTFOUND)
	MESSAGE(WARNING "Allegro primitives library could not be found!")
else()
	MESSAGE(STATUS "Found: " ${ALLEGRO_PRIMITIVES_LIB})
endif (ALLEGRO_PRIMITIVES_LIB_NOTFOUND)

add_executable(NN ${SOURCES})
target_link_libraries(NN ${ALLEGRO_LIB})
target_link_libraries(NN ${ALLEGRO_PRIMITIVES_LIB})
