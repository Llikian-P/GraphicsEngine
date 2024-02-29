#pragma once

// Standard C++ Library Headers
#include <vector>

// External Library Headers
#include "glad/glad.h"

// User-Defined Headers
#include "maths/vec2.hpp"
#include "maths/vec3.hpp"
#include "maths/vec4.hpp"

class Mesh {
public:
    Mesh(unsigned primitive = GL_TRIANGLES);
    Mesh(const Mesh& mesh);
    Mesh& operator =(const Mesh& mesh);

    ~Mesh();

    void position(float x, float y, float z);
    void position(const Point& position);

    void normal(float x, float y, float z);
    void normal(const Vector& normal);

    void color(float r, float g, float b, float a = 1.0f);
    void color(const Color& color);

    void texcoord(float x, float y);
    void texcoord(const TexCoord& texcoord);

    void index(unsigned index);
    void triangle(unsigned top, unsigned left, unsigned right);
    void face(unsigned topLeft, unsigned bottomLeft, unsigned bottomRight, unsigned topRight);

    void updatePosition(unsigned index, float x, float y, float z);
    void updatePosition(unsigned index, const Point& position);

    void updateNormal(unsigned index, float x, float y, float z);
    void updateNormal(unsigned index, const Vector& normal);

    void updateColor(unsigned index, float r, float g, float b, float a = 1.0f);
    void updateColor(unsigned index, const Color& color);

    void updateTexcoord(unsigned index, float x, float y);
    void updateTexcoord(unsigned index, const TexCoord& texcoord);

    void draw();

    const std::vector<Point>* getPositions();
    const std::vector<Vector>* getNormals();
    const std::vector<Color>* getColors();
    const std::vector<TexCoord>* getTexcoords();
    const std::vector<unsigned>* getIndices();

private:
    [[nodiscard]] unsigned long long positionsSize() const;
    [[nodiscard]] unsigned long long normalsSize() const;
    [[nodiscard]] unsigned long long colorsSize() const;
    [[nodiscard]] unsigned long long texcoordsSize() const;
    [[nodiscard]] unsigned long long indicesSize() const;

    void bindBuffers();

    bool buffersUpdate;

    unsigned primitive;

    std::vector<Point> positions;
    std::vector<Vector> normals;
    std::vector<Color> colors;
    std::vector<TexCoord> texcoords;
    std::vector<unsigned> indices;

    unsigned VAO;
    unsigned EBO;
    unsigned positionsVBO;
    unsigned normalsVBO;
    unsigned colorsVBO;
    unsigned texcoordsVBO;
};