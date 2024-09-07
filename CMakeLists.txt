cmake_minimum_required(VERSION 3.28)
project(Version11)

set(CMAKE_CXX_STANDARD 11)

add_executable(Version11
        Includes.h
        Player.cpp
        Player.h
        Die.cpp
        Die.h
        Application.cpp
        Application.h
        MainMenu.cpp
        MainMenu.h
        mainDriver.cpp)
