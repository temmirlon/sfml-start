cmake_minimum_required(VERSION 3.20)

project(sfml_start)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sfml_start
    src/main.cpp
    src/Game.cpp
)

find_package(SFML 2.6 REQUIRED COMPONENTS graphics window system)

target_link_libraries(sfml_start PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)