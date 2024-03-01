/******************************************************************************************************
 * @file  Application.hpp
 * @brief Declaration of the Application class
 ******************************************************************************************************/

#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <map>

#include "Camera.hpp"
#include "Light.hpp"
#include "meshes.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

Point2D getMousePos(GLFWwindow* window);

class Application {
public:
    Application(const char* title, int width, int height);
    ~Application();

    void run();

private:
    void processInputs();

    void bindTexture(const Texture& texture = Texture{}) const;

    void setModel(const Matrix4& model);

    void updateUniforms() const;

    void toggleWireframe();
    void toggleCullface();
    void toggleCursorVisibility();

    void processFirstPersonInputs();
    void processThirdPersonInputs();

    bool getKey(int key);
    void releaseKey(int key);
    void toggleFlag(int key, bool& flag);

    bool wireframe;
    bool cullface;
    bool isCursorActive;
    bool isAxisDrawn;
    bool isGridDrawn;

    GLFWwindow* window;
    Shader* defaultShader;
    Shader* lightShader;
    Shader* noLightShader;

    Light light;

    bool camera;
    FirstPerson camera1st;
    ThirdPerson camera3rd;

    float time;
    float delta;

    Point2D mousePos;
    Point2D oldMousePos;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;

    std::map<int, bool> keyFlags;
};