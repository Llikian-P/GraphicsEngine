/******************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 ******************************************************************************************************/

#include "Application.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

Application::Application(unsigned int width, unsigned int height) {
    if(!glfwInit()) {
        const char* error;
        glfwGetError(&error);
        throw std::runtime_error(std::string("glfwInit failed : ") + error);
    }
    std::cout << "LOG : Initialized GLFW.\n";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, "Graphics Engine", nullptr, nullptr);
    if(!window) {
        const char* error;
        glfwGetError(&error);
        throw std::runtime_error(std::string("glfwCreateWindow failed : ") + error);
    }
    std::cout << "LOG : Created window.\n";

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error("gladLoadGLLoader failed");
    }
    std::cout << "LOG : Initialized GLAD.\n";

    glViewport(0, 0, width, height);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

Application::~Application() {
    glfwDestroyWindow(window);
    std::cout << "LOG : Destroyed window.\n";

    glfwTerminate();
    std::cout << "LOG : Terminated GLFW.\n";
}

void Application::run() {

}