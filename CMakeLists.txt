cmake_minimum_required(VERSION 3.15)
project(Cpp_Snake)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "-Wall -lncurses")
set(CURSES_NEED_NCURSES TRUE)
set(SOURCE_FILES main.cpp)

find_package(Curses REQUIRED)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if (CURSES_FOUND AND CURSES_HAVE_NCURSES_H)
    include_directories(${CURSES_INCLUDE_DIR})
    target_link_libraries (${PROJECT_NAME} ${CURSES_LIBRARIES})
endif()
