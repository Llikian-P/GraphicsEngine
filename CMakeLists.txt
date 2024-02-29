cmake_minimum_required(VERSION 3.26)
project(GraphicsEngine)

###

add_executable(${PROJECT_NAME}
        # Main
        src/main.cpp

        # Libraries
        lib/glad/src/glad.c

        # Sources
        src/Application.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC lib/glad/include)
target_include_directories(${PROJECT_NAME} PUBLIC lib/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_directories(${PROJECT_NAME} PUBLIC lib/glfw/src)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw3)

###
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)