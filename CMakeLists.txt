cmake_minimum_required(VERSION 3.26)
project(GraphicsEngine)
set(NAME graphics_engine)

###

add_executable(${NAME}
        src/main.cpp
)

target_include_directories(${NAME} PUBLIC extern/glad/include)
target_include_directories(${NAME} PUBLIC extern/glfw/include)
target_include_directories(${NAME} PUBLIC include)

target_link_directories(${NAME} PUBLIC extern/glfw/src)
target_link_libraries(${NAME} PUBLIC glfw3)

###
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)