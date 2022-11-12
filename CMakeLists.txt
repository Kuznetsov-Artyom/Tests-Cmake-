cmake_minimum_required(VERSION 3.0.0)

project(homework_one)

set(SRC sources/vectors.cpp sources/matrix.cpp sources/matrixs.cpp)
set(HDR headers/vectors.hpp headers/matrix.hpp headers/matrixs.hpp)

include_directories(.)
add_library(func_lib ${SRC} ${HDR})

 find_package(OpenMP)

if (OpenMP_FOUND)
    message(STATUS "OpenMP - TRUE")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")

else()
    message(STATUS "OpenMP - FALSE")
    
endif()


add_executable(homework_one main.cpp)
target_link_libraries(homework_one func_lib)




