cmake_minimum_required(VERSION 3.24)
project(fms_2)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-lglut -lGL")

add_executable(fms_2 main.cpp  gutils.h Game.cpp Game.h gutils.cpp stdafx.h)
