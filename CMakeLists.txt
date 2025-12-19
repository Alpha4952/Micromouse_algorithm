cmake_minimum_required(VERSION 4.0)
project(Micromouse_v2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Micromouse_v2
        main.c
        map_track_alg.c
        map_track_alg.h)
