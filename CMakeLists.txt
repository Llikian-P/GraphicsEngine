cmake_minimum_required(VERSION 3.26)
project(GraphicsEngine)

set(CMAKE_CXX_STANDARD 23)

find_package(OpenGL REQUIRED)

add_executable(${PROJECT_NAME}
		# Main
        src/main.cpp

		# Sources
        src/Application.cpp
        src/Camera.cpp
        src/ImageData.cpp
        src/Light.cpp
        src/Mesh.cpp
        src/meshes.cpp
        src/Shader.cpp
        src/Texture.cpp

		# Maths
        src/maths/functions.cpp
        src/maths/Matrix4.cpp
        src/maths/transformations.cpp
        src/maths/vec2.cpp
        src/maths/vec3.cpp
        src/maths/vec4.cpp

		# Glad
        lib/glad/src/glad.c

        # Imgui
        lib/imgui/imgui.cpp
        lib/imgui/imgui_draw.cpp
        lib/imgui/imgui_tables.cpp
        lib/imgui/imgui_widgets.cpp
        lib/imgui/imgui_draw.cpp
        lib/imgui/backends/imgui_impl_glfw.cpp
        lib/imgui/backends/imgui_impl_opengl3.cpp

        # Stb
        lib/stb/stb_image.cpp
        lib/stb/stb_image_write.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC lib/glfw/include)
target_include_directories(${PROJECT_NAME} PUBLIC lib/glad/include)
target_include_directories(${PROJECT_NAME} PUBLIC lib/imgui)
target_include_directories(${PROJECT_NAME} PUBLIC lib/stb)

target_link_directories(${PROJECT_NAME} PUBLIC lib/glfw/src)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw3)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)