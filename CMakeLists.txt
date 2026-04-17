cmake_minimum_required(VERSION 3.28)
project(Tarea3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Tarea3 main.cpp 
               Entity.h
               Entity.cpp
               CommandCenter.h
               CommandCenter.cpp)
