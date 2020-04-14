cmake_minimum_required(VERSION 3.13)

set(Includes
    Attribute.hpp
    IndentData.hpp
    RenderComponent.hpp
    RenderElement.hpp
    RenderManager.hpp
)

target_sources(${PROJECT_NAME} PRIVATE ${Includes})

add_subdirectory(Common)