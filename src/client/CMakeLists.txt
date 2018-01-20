cmake_minimum_required(VERSION 3.0)

project(client)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
find_package(PythonLibs REQUIRED)
include_directories(${PYTHON_INCLUDE_DIRS})
find_package (Threads)

set(SRCS main.c)    
set(HEADERS main.h)

add_executable(client ${SRCS} ${HEADERS})
target_link_libraries(client ${CURSES_LIBRARIES} ${PYTHON_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})