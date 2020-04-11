# Main CMake file for Thoth

cmake_minimum_required(VERSION 3.13)

project(Thoth VERSION 0.0.0 LANGUAGES CXX)

message(STATUS "Building with ${PROJECT_NAME} library version ${PROJECT_VERSION}")

# Require C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)

# Include public facing header files
target_include_directories(${PROJECT_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)