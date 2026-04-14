cmake_minimum_required(VERSION 3.20)

project(sfml_start)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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

if(WIN32)
    add_custom_command(TARGET sfml_start POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:sfml_start>
        COMMAND_EXPAND_LISTS
    )
endif()
