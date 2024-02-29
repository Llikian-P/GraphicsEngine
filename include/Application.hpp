/******************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 ******************************************************************************************************/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * @class Application
 * @brief
 */
class Application {
private:
    GLFWwindow* window;

public:
    Application(unsigned int width, unsigned int height);
    ~Application();

    void run();
};