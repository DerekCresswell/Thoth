cmake_minimum_required(VERSION 3.13)

set(src_Sources
    IndentData.cpp
    RenderComponent.cpp
    RenderElement.cpp
    RenderManager.cpp
)

# Create Thoth library
add_library(${PROJECT_NAME}
    ${src_Sources}
)