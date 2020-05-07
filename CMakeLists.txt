# Main CMake file for Thoth
# --------------------------------------------------------

cmake_minimum_required(VERSION 3.13)

project(Thoth VERSION 0.0.0 LANGUAGES CXX)

message(STATUS "Building with ${PROJECT_NAME} library version ${PROJECT_VERSION}")

# Require C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create empty Thoth library
add_library(${PROJECT_NAME} "")

# Set include paths
target_include_directories(${PROJECT_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(include/Thoth)

# Template for all subdir CMake files
# --------------------------------------------------------

#[[

cmake_minimum_required(VERSION 3.13)

set(/dir_path_(Sources||Includes)/
    file.(c||h)pp
    # ...
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${/dir_path_(Sources||Includes)/}
)

# Add any subdirectories

]]

# Explanation
# * First set a variable containing all of the source files.
#   * The name of this variable should be the path to the directory (less src
#   or include) seperated with underscores. Finally it should conclude with
#   Sources or Includes depending on which directory it hails from.
# * Then set the Thoth library to include these sources.
#   * Apply the indentation shown in the example.
# * Then add any subdirectories of the file.