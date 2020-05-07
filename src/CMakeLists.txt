cmake_minimum_required(VERSION 3.13)

set(Sources
    Attribute.cpp
    IndentData.cpp
    RenderComponent.cpp
    RenderElement.cpp
    RenderManager.cpp
)

target_sources(${PROJECT_NAME}
    PRIVATE
        ${Sources}
)