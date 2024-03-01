/******************************************************************************************************
 * @file  Shader.cpp
 * @brief Implementation of the Shader class
 ******************************************************************************************************/

#include "Shader.hpp"

#include <fstream>
#include <glad/glad.h>
#include <iostream>
#include <sstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) : id(glCreateProgram()) {
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

    std::stringstream fragmentStream;
    fragmentStream << fragmentFile.rdbuf();
    std::string fragmentCode = fragmentStream.str();
    const char* fragmentShader = fragmentCode.c_str();

    vertexFile.close();
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

        std::stringstream error;
        error << "Failed to compile vertex shader:\n" << message;

        delete[] message;
        throw std::runtime_error{error.str()};
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

        std::stringstream error;
        error << "Failed to compile fragment shader:\n" << message;

        delete[] message;
        throw std::runtime_error{error.str()};
    }

    /* Link Shaders */
    glAttachShader(id, vertexID);
    glAttachShader(id, fragmentID);
    glLinkProgram(id);

    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if(!success) {
        int length;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);

        char* message = new char[length];
        glGetProgramInfoLog(id, length, &length, message);

        std::stringstream error;
        error << "Failed to link shader program:\n" << message;

        delete[] message;
        throw std::runtime_error{error.str()};
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