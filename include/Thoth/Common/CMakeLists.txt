cmake_minimum_required(VERSION 3.13)

set(Common_Includes
    Attributes.hpp
)

target_sources(${PROJECT_NAME} PRIVATE ${Common_Includes})