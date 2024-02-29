/******************************************************************************************************
 * @file  callbacks.cpp
 * @brief Implementation of the callback functions for GLFW
 ******************************************************************************************************/

#include "callbacks.hpp"

void framebufferSizeCallback(GLFWwindow* /* window */, int width, int height)
{
    glViewport(0, 0, width, height);
}