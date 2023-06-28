cmake_minimum_required(VERSION 3.25)
project(Gengine2 CUDA)

set(CMAKE_CUDA_STANDARD 20)

add_executable(Gengine2 main.cu)
target_link_libraries(Gengine2 GL glut)
set_target_properties(Gengine2 PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
