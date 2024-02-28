cmake_minimum_required(VERSION 3.26)
project(GraphicsEngine)

set(NAME graphics_engine)

add_executable(${NAME}
        src/main.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)