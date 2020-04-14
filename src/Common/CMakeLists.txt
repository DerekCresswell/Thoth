cmake_minimum_required(VERSION 3.13)

set(Common_Sources
    Attributes.cpp
)

target_sources(${PROJECT_NAME} PRIVATE ${Common_Sources})