cmake_minimum_required(VERSION 3.20)
project(path_algorithm)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 CONFIG REQUIRED
        Core
        Widgets
        Gui
        )

add_subdirectory(src)
