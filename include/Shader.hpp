/******************************************************************************************************
 * @file  Shader.hpp
 * @brief Declaration of the Shader class
 ******************************************************************************************************/

#pragma once

#include <string>

#include "maths/vec2.hpp"
#include "maths/vec3.hpp"
#include "maths/vec4.hpp"
#include "maths/Matrix4.hpp"

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use() const;

    void setUniform(const std::string& uniform, int value) const;
    void setUniform(const std::string& uniform, bool value) const;
    void setUniform(const std::string& uniform, float value) const;
    void setUniform(const std::string& uniform, float x, float y) const;
    void setUniform(const std::string& uniform, float x, float y, float z) const;
    void setUniform(const std::string& uniform, float x, float y, float z, float w) const;
    void setUniform(const std::string& uniform, const vec2& vec) const;
    void setUniform(const std::string& uniform, const vec3& vec) const;
    void setUniform(const std::string& uniform, const vec4& vec) const;
    void setUniform(const std::string& uniform, const Matrix4& matrix) const;

    const unsigned int id;
};