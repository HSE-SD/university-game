cmake_minimum_required(VERSION 3.16)

project(University_game)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR C:/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib/cmake/SFML)
set(SFML_INCLUDE_DIR "C:/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/include")
set(SFML_LIBRARY_DIR "C:/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit/SFML-2.5.1/lib")
include_directories(${SFML_INCLUDE_DIR})

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(University_game main.cpp
        constants/constants.h
        entities/player.h
        entities/player.cpp
        entities/teacher.h
        entities/teacher.cpp
        inventory/item.h
        quest/quest.h
        map/game.h
        map/game.cpp
        app_runner/buttons.h
        states/state.h
        states/OnKeyPressed.cpp
        states/Application.cpp
        states/DrawingStarted.cpp
)

# Use this bad boy to create your own quests:
# add_executable(University_game construct_quest.cpp)

target_link_libraries(University_game sfml-graphics sfml-audio)


