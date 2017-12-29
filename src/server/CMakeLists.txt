cmake_minimum_required(VERSION 3.0)

project(server)

find_package(Threads)

set(SRCS main.c menu.c socket.c ../lib/fonts/font.c)
set(HEADERS menu.h socket.h ../lib/fonts/font.h)

add_executable(server ${SRCS} ${HEADERS})
target_link_libraries(server ${CMAKE_THREAD_LIBS_INIT})
