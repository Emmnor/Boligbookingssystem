cmake_minimum_required(VERSION 3.20)
project(gruppe77)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(gruppe77
    bolig.cpp
    bolig.h
    enebolig.cpp
    enebolig.h
    enum.h
    funksjoner.cpp
    funksjoner.h
    kunde.cpp
    kunde.h
    kunder.cpp
    kunder.h
    LesData3.cpp
    LesData3.h
    Main.cpp
    sone.cpp
    sone.h
    soner.cpp
    soner.h)
