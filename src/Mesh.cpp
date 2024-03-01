/******************************************************************************************************
 * @file  Mesh.cpp
 * @brief Implementation of the Mesh class
 ******************************************************************************************************/

#include "Mesh.hpp"

#include <stdexcept>

Mesh::Mesh(unsigned primitive) : positions{}, colors{}, primitive{primitive}, buffersUpdate{true} {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &positionsVBO);
    glGenBuffers(1, &normalsVBO);
    glGenBuffers(1, &colorsVBO);
    glGenBuffers(1, &texcoordsVBO);
    glGenBuffers(1, &EBO);
}

Mesh::Mesh(const Mesh& mesh) {
    if(this == &mesh) { return; }

    buffersUpdate = true;

    primitive = mesh.primitive;

    positions = mesh.positions;
    normals = mesh.normals;
    colors = mesh.colors;
    texcoords = mesh.texcoords;
    indices = mesh.indices;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &positionsVBO);
    glGenBuffers(1, &normalsVBO);
    glGenBuffers(1, &colorsVBO);
    glGenBuffers(1, &texcoordsVBO);
    glGenBuffers(1, &EBO);
}

Mesh& Mesh::operator =(const Mesh& mesh) {
    if(this == &mesh) { return *this; }

    buffersUpdate = true;

    primitive = mesh.primitive;

    positions = mesh.positions;
    normals = mesh.normals;
    colors = mesh.colors;
    texcoords = mesh.texcoords;
    indices = mesh.indices;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &positionsVBO);
    glGenBuffers(1, &normalsVBO);
    glGenBuffers(1, &colorsVBO);
    glGenBuffers(1, &texcoordsVBO);
    glGenBuffers(1, &EBO);

    return *this;
}


Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &positionsVBO);
    glDeleteBuffers(1, &normalsVBO);
    glDeleteBuffers(1, &colorsVBO);
    glDeleteBuffers(1, &texcoordsVBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::position(float x, float y, float z) {
    positions.emplace_back(x, y, z);

    if(!normals.empty() && normals.size() < positions.size()) {
        normals.push_back(normals[normals.size() - 1]);
    }

    if(colors.empty()) {
        colors.emplace_back(1.0f, 1.0f, 1.0f, 1.0f);
    } else if(colors.size() < positions.size()) {
        colors.push_back(colors[colors.size() - 1]);
    }

    if(!texcoords.empty() && texcoords.size() < positions.size()) {
        texcoords.push_back(texcoords[texcoords.size() - 1]);
    }

    buffersUpdate = true;
}

void Mesh::position(const Point& position) {
    Mesh::position(position.x, position.y, position.z);
}

void Mesh::normal(float x, float y, float z) {
    if(normals.size() <= positions.size()) {
        normals.emplace_back(x, y, z);
    }
}

void Mesh::normal(const Vector& normal) {
    if(normals.size() <= positions.size()) {
        normals.push_back(normal);
    }
}

void Mesh::color(float r, float g, float b, float a) {
    if(colors.size() <= positions.size()) {
        colors.emplace_back(r, g, b, a);
    }
}

void Mesh::color(const Color& color) {
    if(colors.size() <= positions.size()) {
        colors.push_back(color);
    }
}

void Mesh::texcoord(float x, float y) {
    if(texcoords.size() <= positions.size()) {
        texcoords.emplace_back(x, y);
    }
}

void Mesh::texcoord(const TexCoord& texcoord) {
    if(texcoords.size() <= positions.size()) {
        texcoords.push_back(texcoord);
    }
}

void Mesh::index(unsigned index) {
    indices.push_back(index);
}

void Mesh::triangle(unsigned top, unsigned left, unsigned right) {
    index(top);
    index(left);
    index(right);
}

void Mesh::face(unsigned topLeft, unsigned bottomLeft, unsigned bottomRight, unsigned topRight) {
    triangle(topLeft, bottomLeft, bottomRight);
    triangle(topLeft, bottomRight, topRight);
}

void Mesh::updatePosition(unsigned index, float x, float y, float z) {
    positions[index].x = x;
    positions[index].y = y;
    positions[index].z = z;

    buffersUpdate = true;
}

void Mesh::updatePosition(unsigned index, const Point& position) {
    positions[index] = position;

    buffersUpdate = true;
}

void Mesh::updateNormal(unsigned index, float x, float y, float z) {
    normals[index].x = x;
    normals[index].y = y;
    normals[index].z = z;

    buffersUpdate = true;
}

void Mesh::updateNormal(unsigned index, const Vector& normal) {
    normals[index] = normal;

    buffersUpdate = true;
}

void Mesh::updateColor(unsigned index, float r, float g, float b, float a) {
    colors[index].r = r;
    colors[index].g = g;
    colors[index].b = b;
    colors[index].a = a;

    buffersUpdate = true;
}

void Mesh::updateColor(unsigned index, const Color& color) {
    colors[index] = color;

    buffersUpdate = true;
}

void Mesh::updateTexcoord(unsigned index, float x, float y) {
    texcoords[index].x = x;
    texcoords[index].y = y;

    buffersUpdate = true;
}

void Mesh::updateTexcoord(unsigned index, const TexCoord& texcoord) {
    texcoords[index] = texcoord;

    buffersUpdate = true;
}

void Mesh::draw() {
    if(buffersUpdate) {
        bindBuffers();
        buffersUpdate = false;
    }

    glBindVertexArray(VAO);

    if(indices.empty()) {
        glDrawArrays(primitive, 0, static_cast<int>(positions.size()));
    } else {
        glDrawElements(primitive, static_cast<int>(indices.size()), GL_UNSIGNED_INT, nullptr);
    }
}

void Mesh::bindBuffers() {
    if(positions.empty()) {
        throw std::runtime_error{"Nothing to bind in Mesh"};
    }

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, positionsVBO);
    glBufferData(GL_ARRAY_BUFFER, positionsSize(), &positions[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    if(normals.empty() && !indices.empty() && primitive == GL_TRIANGLES) {
        normals.resize(positions.size());

        Vector temp;

        // Indices of a face: 0-1-2  0-2-3
        for(int i = 0 ; i < indices.size() ; i += 6) {
            temp = cross(positions[indices[i + 2]] - positions[indices[i + 1]], positions[indices[i]] - positions[indices[i + 1]]);

            normals[indices[i]] += temp;
            normals[indices[i + 1]] += temp;
            normals[indices[i + 2]] += temp;
            normals[indices[i + 5]] += temp;
        }

        for(auto& normal: normals) {
            normal = normalize(normal);
        }
    }

    if(!normals.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
        glBufferData(GL_ARRAY_BUFFER, normalsSize(), &normals[0], GL_STATIC_DRAW);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
        glEnableVertexAttribArray(1);
    }

    glBindBuffer(GL_ARRAY_BUFFER, colorsVBO);
    glBufferData(GL_ARRAY_BUFFER, colorsSize(), &colors[0], GL_STATIC_DRAW);

    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(2);

    if(!texcoords.empty()) {
        glBindBuffer(GL_ARRAY_BUFFER, texcoordsVBO);
        glBufferData(GL_ARRAY_BUFFER, texcoordsSize(), &texcoords[0], GL_STATIC_DRAW);

        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
        glEnableVertexAttribArray(3);
    }

    if(!indices.empty()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize(), &indices[0], GL_STATIC_DRAW);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

const std::vector<Point>* Mesh::getPositions() {
    return &positions;
}

const std::vector<Vector>* Mesh::getNormals() {
    return &normals;
}

const std::vector<Color>* Mesh::getColors() {
    return &colors;
}

const std::vector<TexCoord>* Mesh::getTexcoords() {
    return &texcoords;
}

const std::vector<unsigned>* Mesh::getIndices() {
    return &indices;
}

unsigned long long Mesh::positionsSize() const {
    return positions.size() * sizeof(Point);
}

unsigned long long Mesh::normalsSize() const {
    return normals.size() * sizeof(Vector);
}

unsigned long long Mesh::colorsSize() const {
    return colors.size() * sizeof(Color);
}

unsigned long long Mesh::texcoordsSize() const {
    return texcoords.size() * sizeof(TexCoord);
}

unsigned long long Mesh::indicesSize() const {
    return indices.size() * sizeof(unsigned);
}