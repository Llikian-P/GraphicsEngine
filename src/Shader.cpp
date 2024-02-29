// Current File's Header
#include "Shader.hpp"

// Standard C++ Library Headers
#include <fstream>
#include <iostream>
#include <sstream>

// External Library Headers
#include "glad/glad.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    /* Read Shaders */
    std::ifstream vertexFile{vertexPath};
    std::ifstream fragmentFile{fragmentPath};

    if(!vertexFile.is_open()) {
        throw std::runtime_error{"Vertex shader was not found at path: \"" + vertexPath + "\"."};
    }

    if(!fragmentFile.is_open()) {
        throw std::runtime_error{"Fragment shader was not found at path: \"" + fragmentPath + "\"."};
    }

    std::stringstream vertexStream;
    vertexStream << vertexFile.rdbuf();
    std::string vertexCode = vertexStream.str();
    const char* vertexShader = vertexCode.c_str();
    vertexFile.close();

    std::stringstream fragmentStream;
    fragmentStream << fragmentFile.rdbuf();
    std::string fragmentCode = fragmentStream.str();
    const char* fragmentShader = fragmentCode.c_str();
    fragmentFile.close();

    /* Compile Shaders */
    unsigned vertexID, fragmentID;
    int success;

    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vertexShader, nullptr);
    glCompileShader(vertexID);

    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
    if(!success) {
        int length;
        glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];
        glGetShaderInfoLog(vertexID, length, &length, message);

        std::string error = "Failed to compile vertex shader:\n";
        error += message;

        delete[] message;
        throw std::runtime_error{error};
    }

    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fragmentShader, nullptr);
    glCompileShader(fragmentID);

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
    if(!success) {
        int length;
        glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];
        glGetShaderInfoLog(fragmentID, length, &length, message);

        std::string error = "Failed to compile frament shader:\n";
        error += message;

        delete[] message;
        throw std::runtime_error{error};
    }

    /* Link Shaders */
    id = glCreateProgram();
    glAttachShader(id, vertexID);
    glAttachShader(id, fragmentID);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        int length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];
        glGetProgramInfoLog(id, length, &length, message);

        std::string error = "Failed to link shader program:\n";
        error += message;

        delete[] message;
        throw std::runtime_error{error};
    }

    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
}

Shader::~Shader() {
    glDeleteProgram(id);
}

void Shader::use() const {
    glUseProgram(id);
}

int Shader::getId() const {
    return static_cast<int>(id);
}

void Shader::setUniform(const std::string& uniform, int value) const {
    glUniform1i(glGetUniformLocation(id, uniform.c_str()), value);
}

void Shader::setUniform(const std::string& uniform, bool value) const {
    glUniform1i(glGetUniformLocation(id, uniform.c_str()), static_cast<int>(value));
}

void Shader::setUniform(const std::string& uniform, float value) const {
    glUniform1f(glGetUniformLocation(id, uniform.c_str()), value);
}

void Shader::setUniform(const std::string& uniform, float x, float y) const {
    glUniform2f(glGetUniformLocation(id, uniform.c_str()), x, y);
}

void Shader::setUniform(const std::string& uniform, float x, float y, float z) const {
    glUniform3f(glGetUniformLocation(id, uniform.c_str()), x, y, z);
}

void Shader::setUniform(const std::string& uniform, float x, float y, float z, float w) const {
    glUniform4f(glGetUniformLocation(id, uniform.c_str()), x, y, z, w);
}

void Shader::setUniform(const std::string& uniform, const vec2& vec) const {
    glUniform2fv(glGetUniformLocation(id, uniform.c_str()), 1, &vec.x);
}

void Shader::setUniform(const std::string& uniform, const vec3& vec) const {
    glUniform3fv(glGetUniformLocation(id, uniform.c_str()), 1, &vec.x);
}

void Shader::setUniform(const std::string& uniform, const vec4& vec) const {
    glUniform4fv(glGetUniformLocation(id, uniform.c_str()), 1, &vec.x);
}

void Shader::setUniform(const std::string& uniform, const Matrix4& matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(id, uniform.c_str()), 1, true, &matrix.values[0][0]);
}