/******************************************************************************************************
 * @file  Application.cpp
 * @brief Implementation of the Application class
 ******************************************************************************************************/

#include "Application.hpp"

#include <cmath>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <iostream>
#include <stdexcept>

#include "ImageData.hpp"
#include "Mesh.hpp"
#include "maths/transformations.hpp"

void framebufferSizeCallback(GLFWwindow* /* window */, int width, int height) {
    glViewport(0, 0, width, height);
}

Point2D getMousePos(GLFWwindow* window) {
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);

    return Point2D{static_cast<float>(xPos), static_cast<float>(yPos)};
}

Application::Application(const char* title, int width, int height)
    : isAxisDrawn{true}, isGridDrawn{true}, wireframe{}, cullface{true}, isCursorActive{true},
      window{}, defaultShader{}, lightShader{},
      light{Point{10.f, 10.f, 10.f}, White(), White(), White()},
      camera{false}, camera1st{Point{0.0f, 2.0f, 7.5f}}, camera3rd{Point{0.0f, 5.0f, 7.5f}},
      time{}, delta{},
      mousePos{}, oldMousePos{},
      keyFlags{} {

    /* GLFW & GLAD */
    if(!glfwInit()) {
        const char* error;
        glfwGetError(&error);
        throw std::runtime_error{std::string("Failed to initialize GLFW : ").append(error)};
    }
    std::cout << "LOG : Initialized GLFW.\n";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if(!(window = glfwCreateWindow(width, height, title, nullptr, nullptr))) {
        throw std::runtime_error{"Failed to create window"};
    }
    std::cout << "LOG : Created window.\n";

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if(!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        throw std::runtime_error{"Failed to initialize GLAD"};
    }
    std::cout << "LOG : Initialized GLAD.\n";

    glViewport(0, 0, width, height);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // todo: Find a crossplatform way to get the size of the display
    glfwSetWindowPos(window, (1920 - width) / 2, (1080 - height) / 2);
    glfwSetCursorPos(window, width / 2.0, height / 2.0);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    /* ImGui */
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    std::cout << "LOG : Created ImGui context.\n";

    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    ImGui::GetIO().IniFilename = "lib/imgui/imgui.ini";

    /* Other things to set up */
    defaultShader = new Shader{"data/shaders/default.vert", "data/shaders/default.frag"};
    lightShader = new Shader{"data/shaders/light.vert", "data/shaders/light.frag"};
    noLightShader = new Shader{"data/shaders/noLight.vert", "data/shaders/noLight.frag"};
    std::cout << "LOG : Created shader programs.\n";
}

Application::~Application() {
    delete defaultShader;
    delete lightShader;
    delete noLightShader;
    std::cout << "LOG : Deleted shaders.\n";

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    std::cout << "LOG : Terminated ImGui.\n";

    glfwDestroyWindow(window);
    std::cout << "LOG : Destroyed window.\n";
    glfwTerminate();
    std::cout << "LOG : Terminated GLFW.\n";
}

void Application::run() {
    Texture ceres(ImageData("data/textures/ceres.jpg"));
//    Texture earth(ImageData("data/textures/earth.jpg"));
//    Texture earth_clouds(ImageData("data/textures/earth_clouds.jpg"));
//    Texture earth_night(ImageData("data/textures/earth_night.jpg"));
//    Texture eris(ImageData("data/textures/eris.jpg"));
//    Texture haumea(ImageData("data/textures/haumea.jpg"));
//    Texture jupiter(ImageData("data/textures/jupiter.jpg"));
//    Texture makemake(ImageData("data/textures/makemake.jpg"));
//    Texture mars(ImageData("data/textures/mars.jpg"));
//    Texture mercury(ImageData("data/textures/mercury.jpg"));
//    Texture moon(ImageData("data/textures/moon.jpg"));
//    Texture neptune(ImageData("data/textures/neptune.jpg"));
//    Texture saturn(ImageData("data/textures/saturn.jpg"));
//    Texture sun(ImageData("data/textures/sun.jpg"));
//    Texture uranus(ImageData("data/textures/uranus.jpg"));
//    Texture venus(ImageData("data/textures/venus.jpg"));
//    Texture texCube(ImageData("data/textures/cube.png"));

    Mesh axis = initAxis(5.0f);
    Mesh grid = initGrid();
    Mesh cube = initCube();
    Mesh disk = initDisk();
    Mesh cylinder = initCylinder();
    Mesh sphere = initSphere();
    Mesh cone = initCone();
    Mesh torus = initTorus();
    Mesh klein = initKleinBottle(256, 256);
    Mesh tube = initTube(Point(-5.0f, 0.0f, 5.0f),
                         Point(-5.0f, 0.0f, -5.0f),
                         Point(5.0f, 0.0f, -5.0f),
                         Point(5.0f, 0.0f, 5.0f));

    RGB background(0.1f);

    light.ambient = vec4(0.2f, 1.0f);
    light.diffuse = vec4(1.0f);
    light.specular = vec4(1.0f);

    ambient = vec4(0.5f, 1.0f);
    diffuse = vec4(1.0f);
    specular = vec4(1.0f);
    shininess = 32.0f;

    while(!glfwWindowShouldClose(window)) {
        glClearColor(background.r, background.g, background.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        light.position = 5.0f * Point{cosf(time), 1.0f, sinf(time)};

        glfwPollEvents();
        processInputs();

        // SHADER FOR OBJECTS NOT INFLUENCED BY LIGHT
        noLightShader->use();
        updateUniforms();

        if(camera) {
            setModel(translate(camera3rd.target) * scale(0.1f));
            sphere.draw();
        }

        setModel(Identity());
        if(isAxisDrawn) { axis.draw(); }
        if(isGridDrawn) { grid.draw(); }

        // SHADER FOR LIGHTS
        lightShader->use();
        updateUniforms();

        setModel(translate(light.position) * scale(0.2f));
        sphere.draw();

        // DEFAULT SHADER
        defaultShader->use();
        updateUniforms();

        setModel(Identity());
        bindTexture(ceres);
        sphere.draw();

//        setModel(translate(3.0f, 0.0f, 0.0f) * rotateY(45.0f));
//        bindTexture(texCube);
//        cube.draw();
//
//        setModel(translate(-3.0f, 0.0f, 0.0f));
//        bindTexture();
//        cylinder.draw();

//        setModel(rotateX(90.0f));
//        bindTexture();
//        klein.draw();

//        setModel(Identity());
//        bindTexture();
//        tube.draw();

        /* ImGui Window */ {
            ImGui::Begin("Controls");

            if(ImGui::Button("Toggle Wireframe (W)")) { toggleWireframe(); }
            ImGui::SameLine();
            if(ImGui::Button("Toggle Cullface (C)")) { toggleCullface(); }
            ImGui::SameLine();
            if(ImGui::Button("Toggle Cursor (F1)")) { toggleCursorVisibility(); }

            ImGui::Checkbox("Axis (A)", &isAxisDrawn);
            ImGui::SameLine();
            ImGui::Checkbox("Grid (G)", &isGridDrawn);
            if(camera) {
                if(ImGui::Button("Camera - Third Person (F5)")) { camera = !camera; }
            } else {
                if(ImGui::Button("Camera - First Person (F5)")) { camera = !camera; }
            }

            ImGui::ColorEdit3("Background Color", &background.r);

            ImGui::Text("First Person Camera :");
            ImGui::InputFloat3("Position (FP)", &camera1st.position.x);
            ImGui::InputFloat("Yaw (FP)", &camera1st.yaw);
            ImGui::InputFloat("Pitch (FP)", &camera1st.pitch);

            ImGui::Text("Third Person Camera :");
            ImGui::InputFloat3("Position (TP)", &camera3rd.position.x);
            ImGui::InputFloat3("Target (TP)", &camera3rd.target.x);
            ImGui::InputFloat("Yaw (TP)", &camera3rd.yaw);
            ImGui::InputFloat("Pitch (TP)", &camera3rd.pitch);

            ImGui::Text("Light :");
            ImGui::InputFloat3("Light Position", &light.position.x);
            ImGui::ColorEdit4("Light Ambient", &light.ambient.x);
            ImGui::ColorEdit4("Light Diffuse", &light.diffuse.x);
            ImGui::ColorEdit4("Light Specular", &light.specular.x);

            ImGui::Text("Material :");
            ImGui::ColorEdit4("Ambient", &ambient.x);
            ImGui::ColorEdit4("Diffuse", &diffuse.x);
            ImGui::ColorEdit4("Specular", &specular.x);
            ImGui::InputFloat("Shininess", &shininess);


            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }
}

void Application::processInputs() {
    delta = static_cast<float>(glfwGetTime()) - time;
    time = static_cast<float>(glfwGetTime());
    mousePos = getMousePos(window);

    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }

    if(getKey(GLFW_KEY_Z)) { toggleWireframe(); }
    releaseKey(GLFW_KEY_Z);

    if(getKey(GLFW_KEY_C)) { toggleCullface(); }
    releaseKey(GLFW_KEY_C);

    if(getKey(GLFW_KEY_F1)) { toggleCursorVisibility(); }
    releaseKey(GLFW_KEY_F1);

    toggleFlag(GLFW_KEY_F5, camera);
    toggleFlag(GLFW_KEY_G, isGridDrawn);
    toggleFlag(GLFW_KEY_Q, isAxisDrawn);

    if(!isCursorActive) { camera ? processThirdPersonInputs() : processFirstPersonInputs(); }

    oldMousePos = mousePos;
}

void Application::bindTexture(const Texture& texture) const {
    texture.bind();
    defaultShader->setUniform("u_hasTexture", texture.getId() != 0);
}

void Application::setModel(const Matrix4& model) {
    int id;
    glGetIntegerv(GL_CURRENT_PROGRAM, &id);

    if(id == defaultShader->id) {
        defaultShader->setUniform("u_model", model);
        defaultShader->setUniform("u_model_inverse", transpose(inverse(model)));
    } else if(id == lightShader->id) {
        lightShader->setUniform("u_model", model);
    } else if(id == noLightShader->id) {
        noLightShader->setUniform("u_model", model);
    }
}

void Application::updateUniforms() const {
    Matrix4 view;
    Point camPos;

    if(camera) {
        view = camera3rd.getLookAt();
        camPos = camera3rd.position;
    } else {
        view = camera1st.getLookAt();
        camPos = camera1st.position;
    }

    int width, height;
    glfwGetWindowSize(window, &width, &height);
    Matrix4 projection = perspective(quarter_pi(), static_cast<float>(width) / static_cast<float>(height), 0.1f, 100.0f);

    int id;
    glGetIntegerv(GL_CURRENT_PROGRAM, &id);

    if(id == defaultShader->id) {
        defaultShader->setUniform("u_view", view);
        defaultShader->setUniform("u_projection", projection);
        defaultShader->setUniform("u_cameraPosition", camPos);

        defaultShader->setUniform("u_light.position", light.position);
        defaultShader->setUniform("u_light.ambient", light.ambient);
        defaultShader->setUniform("u_light.diffuse", light.diffuse);
        defaultShader->setUniform("u_light.specular", light.specular);

        defaultShader->setUniform("u_material.ambient", ambient);
        defaultShader->setUniform("u_material.diffuse", diffuse);
        defaultShader->setUniform("u_material.specular", specular);
        defaultShader->setUniform("u_material.shininess", shininess);
    } else if(id == lightShader->id) {
        lightShader->setUniform("u_view", view);
        lightShader->setUniform("u_projection", projection);
        lightShader->setUniform("u_lightColor", light.diffuse);
    } else if(id == noLightShader->id) {
        noLightShader->setUniform("u_view", view);
        noLightShader->setUniform("u_projection", projection);
    }
}

void Application::toggleWireframe() {
    glPolygonMode(GL_FRONT_AND_BACK, wireframe ? GL_FILL : GL_LINE);
    wireframe = !wireframe;
}

void Application::toggleCullface() {
    cullface ? glDisable(GL_CULL_FACE) : glEnable(GL_CULL_FACE);
    cullface = !cullface;
}

void Application::toggleCursorVisibility() {
    glfwSetInputMode(window, GLFW_CURSOR, isCursorActive ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
    isCursorActive = !isCursorActive;
}

void Application::processFirstPersonInputs() {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { camera1st.processKeyboardInputs(CameraControls::forward, delta); }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { camera1st.processKeyboardInputs(CameraControls::backward, delta); }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { camera1st.processKeyboardInputs(CameraControls::left, delta); }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { camera1st.processKeyboardInputs(CameraControls::right, delta); }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { camera1st.processKeyboardInputs(CameraControls::upward, delta); }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { camera1st.processKeyboardInputs(CameraControls::downward, delta); }

    // Y is reversed since y-coordinates go from bottom to top
    camera1st.processMouseInputs(mousePos.x - oldMousePos.x, oldMousePos.y - mousePos.y);
}

void Application::processThirdPersonInputs() {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { camera3rd.processKeyboardInputs(CameraControls::forward, delta); }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { camera3rd.processKeyboardInputs(CameraControls::backward, delta); }

    // Y is reversed since y-coordinates go from bottom to top
    camera3rd.processMouseInputs(mousePos.x - oldMousePos.x, oldMousePos.y - mousePos.y);
}

bool Application::getKey(int key) {
    if(!keyFlags.contains(key)) {
        keyFlags.emplace(key, false);
        return false;
    }

    bool state = glfwGetKey(window, key) == GLFW_PRESS && !keyFlags.at(key);
    if(state) { keyFlags.at(key) = true; }

    return state;
}

void Application::releaseKey(int key) {
    if(glfwGetKey(window, key) == GLFW_RELEASE) { keyFlags.at(key) = false; }
}

void Application::toggleFlag(int key, bool& flag) {
    if(getKey(key)) { flag = !flag; }
    releaseKey(key);
}