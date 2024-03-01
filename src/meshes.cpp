/******************************************************************************************************
 * @file  meshes.cpp
 * @brief
 ******************************************************************************************************/

#include "meshes.hpp"

#include <cmath>

#include "maths/constants.hpp"
#include "maths/functions.hpp"
#include "maths/transformations.hpp"
#include "maths/vec2.hpp"

Mesh initAxis(float length) {
    Mesh mesh{GL_LINES};

    mesh.color(1.0f, 0.0f, 0.0f);
    mesh.position(0.0f, 0.0f, 0.0f);
    mesh.position(length, 0.0f, 0.0f);

    mesh.color(0.0f, 1.0f, 0.0f);
    mesh.position(0.0f, 0.0f, 0.0f);
    mesh.position(0.0f, length, 0.0f);

    mesh.color(0.0f, 0.0f, 1.0f);
    mesh.position(0.0f, 0.0f, 0.0f);
    mesh.position(0.0f, 0.0f, length);

    return mesh;
}

Mesh initGrid(int sizeX, int sizeZ) {
    Mesh mesh{GL_LINES};

    mesh.color(1.0f, 1.0f, 1.0f);

    for(int i = -sizeX ; i <= sizeX ; ++i) {
        for(int j = -sizeZ ; j <= sizeZ ; ++j) {
            mesh.position(static_cast<float>(-sizeX), 0.0f, static_cast<float>(j));
            mesh.position(static_cast<float>(sizeX), 0.0f, static_cast<float>(j));

            mesh.position(static_cast<float>(i), 0.0f, static_cast<float>(-sizeZ));
            mesh.position(static_cast<float>(i), 0.0f, static_cast<float>(sizeZ));
        }
    }

    return mesh;
}

Mesh initCube() {
    Mesh mesh{GL_TRIANGLES};

    /* Vertices' index
     *  0–––3
     *  |\  |\
     *  | 1–––2
     *  4–|–7 |
     *   \|  \|
     *    5–––6
     */

    /* Faces & Template
     *       0     3
     *       |¯¯¯¯¯|
     *       |  0  |
     * 0    1|     |2    3     0
     * |¯¯¯¯¯|¯¯¯¯¯|¯¯¯¯¯|¯¯¯¯¯|
     * |  1  |  2  |  3  |  4  |
     * |_ _ _|_ _ _|_ _ _|_ _ _|
     * 4    5|     |6    7     4
     *       |  5  |
     *      4|_ _ _|7
     */

    Point vertices[8]{Point{-1.0f, 1.0f, -1.0f},
                      Point{-1.0f, 1.0f, 1.0f},
                      Point{1.0f, 1.0f, 1.0f},
                      Point{1.0f, 1.0f, -1.0f},
                      Point{-1.0f, -1.0f, -1.0f},
                      Point{-1.0f, -1.0f, 1.0f},
                      Point{1.0f, -1.0f, 1.0f},
                      Point{1.0f, -1.0f, -1.0f}};

    Vector normals[6]{Vector{0.0f, 1.0f, 0.0f},
                      Vector{-1.0f, 0.0f, 0.0f},
                      Vector{0.0f, 0.0f, 1.0f},
                      Vector{1.0f, 0.0f, 0.0f},
                      Vector{0.0f, 0.0f, -1.0f},
                      Vector{0.0f, -1.0f, 0.0f}};

    static constexpr float n1_3 = 1.0f / 3.0f;
    static constexpr float n2_3 = 2.0f / 3.0f;

    TexCoord texcoords[6][4]{{TexCoord{0.25f, 1.0f}, TexCoord{0.25f, n2_3}, TexCoord{0.50f, n2_3}, TexCoord{0.50f, 1.0f}},
                             {TexCoord{0.00f, n2_3}, TexCoord{0.00f, n1_3}, TexCoord{0.25f, n1_3}, TexCoord{0.25f, n2_3}},
                             {TexCoord{0.25f, n2_3}, TexCoord{0.25f, n1_3}, TexCoord{0.50f, n1_3}, TexCoord{0.50f, n2_3}},
                             {TexCoord{0.50f, n2_3}, TexCoord{0.50f, n1_3}, TexCoord{0.75f, n1_3}, TexCoord{0.75f, n2_3}},
                             {TexCoord{0.75f, n2_3}, TexCoord{0.75f, n1_3}, TexCoord{1.00f, n1_3}, TexCoord{1.00f, n2_3}},
                             {TexCoord{0.25f, n1_3}, TexCoord{0.25f, 0.0f}, TexCoord{0.50f, 0.0f}, TexCoord{0.50f, n1_3}}};

    int faces[6][4]{{0, 1, 2, 3},
                    {0, 4, 5, 1},
                    {1, 5, 6, 2},
                    {2, 6, 7, 3},
                    {3, 7, 4, 0},
                    {5, 4, 7, 6}};

    for(int i = 0 ; i < 6 ; ++i) {
        mesh.normal(normals[i]);

        mesh.texcoord(texcoords[i][0]);
        mesh.position(vertices[faces[i][0]]);

        mesh.texcoord(texcoords[i][1]);
        mesh.position(vertices[faces[i][1]]);

        mesh.texcoord(texcoords[i][2]);
        mesh.position(vertices[faces[i][2]]);

        mesh.texcoord(texcoords[i][3]);
        mesh.position(vertices[faces[i][3]]);

        mesh.face((i * 4), (i * 4) + 1, (i * 4) + 2, (i * 4) + 3);
    }

    return mesh;
}

Mesh initDisk(const unsigned div) {
    Mesh mesh{GL_TRIANGLES};

    // alpha ∈ [0 ; 2pi]
    const float step = two_pi() / static_cast<float>(div);
    float alpha = 0.0f;

    mesh.normal(0.0f, 1.0f, 0.0f);

    for(int i = 0 ; i < div ; ++i) {
        mesh.position(cosf(alpha), 0.0f, sinf(alpha));

        alpha += step;
    }

    mesh.position(0.0f, 0.0f, 0.0f);

    for(int i = 0 ; i < div ; ++i) {
        mesh.triangle(div, (i + 1) % div, i);
    }

    return mesh;
}

Mesh initCylinder(unsigned int div) {
    Mesh mesh{GL_TRIANGLES};

    // alpha ∈ [0 ; 2pi]
    const float step = two_pi() / static_cast<float>(div);
    float alpha = 0.0f;

    for(int i = 0 ; i < div ; ++i) {
        mesh.normal(cosf(alpha), 0.0f, sinf(alpha));
        mesh.position(cosf(alpha), 1.0f, sinf(alpha));
        mesh.position(cosf(alpha), -1.0f, sinf(alpha));

        alpha += step;
    }

    for(int i = 0 ; i < div ; ++i) {
        mesh.face(((i + 1) % div) * 2, 1 + ((i + 1) % div) * 2, 1 + i * 2, i * 2);
    }

    return mesh;
}

Mesh initSphere(unsigned int divAlpha, unsigned int divBeta) {
    Mesh mesh{GL_TRIANGLES};

    // alpha ∈ [-pi/2 ; pi/2] and beta ∈ [0, 2pi]
    const float stepAlpha = pi() / static_cast<float>(divAlpha), stepBeta = two_pi() / static_cast<float>(divBeta);
    float alpha = -half_pi(), beta;

    for(int i = 0 ; i <= divAlpha ; ++i) {
        beta = 0.0f;

        for(int j = 0 ; j <= divBeta ; ++j) {
            mesh.texcoord(1.0f - beta / two_pi(), 0.5f + 0.5f * sinf(alpha));
            mesh.normal(cosf(alpha) * cosf(beta), sinf(alpha), cosf(alpha) * sinf(beta));
            mesh.position(cosf(alpha) * cosf(beta), sinf(alpha), cosf(alpha) * sinf(beta));

            beta += stepBeta;
        }

        alpha += stepAlpha;
    }

    auto index = [&](int i, int j) -> unsigned {
        return j + i * (divBeta + 1);
    };

    for(int i = 0 ; i < divAlpha ; ++i) {
        for(int j = 0 ; j < divBeta ; ++j) {
            mesh.face(index(i + 1, j + 1),
                      index(i, j + 1),
                      index(i, j),
                      index(i + 1, j));
        }
    }

    return mesh;
}

Mesh initCone(unsigned int div) {
    Mesh mesh{GL_TRIANGLES};

    // alpha ∈ [0 ; 2pi]
    const float step = two_pi() / static_cast<float>(div);
    float alpha = 0.0f;

    for(int i = 0 ; i < div ; ++i) {
        mesh.normal(root_two_over_two() * cosf(alpha), root_two_over_two(), root_two_over_two() * sinf(alpha));
        mesh.position(cosf(alpha), 0.0f, sinf(alpha));

        alpha += step;
    }

    mesh.normal(0.0f, 0.0f, 0.0f);
    mesh.position(0.0f, 1.0f, 0.0f);

    for(int i = 0 ; i < div ; ++i) {
        mesh.triangle(div, (i + 1) % div, i);
    }

    return mesh;
}

Mesh initTorus(float R, float r, unsigned int divAlpha, unsigned int divBeta) {
    Mesh mesh{GL_TRIANGLES};

    // alpha ∈ [0, 2pi] and beta ∈ [0, 2pi]
    const float stepAlpha = two_pi() / static_cast<float>(divAlpha), stepBeta = two_pi() / static_cast<float>(divBeta);
    float alpha = 0.0f, beta;

    for(int i = 0 ; i <= divAlpha ; ++i) {
        beta = 0.0f;

        for(int j = 0 ; j < divBeta ; ++j) {
            mesh.normal(cosf(alpha) * cosf(beta), sinf(alpha), cosf(alpha) * sinf(beta));
            mesh.position((R + r * cosf(alpha)) * cosf(beta), r * sinf(alpha), (R + r * cosf(alpha)) * sinf(beta));

            beta += stepBeta;
        }

        alpha += stepAlpha;
    }

    auto index = [&](int i, int j) -> unsigned {
        return j % divBeta + divBeta * i;
    };

    for(int i = 0 ; i < divAlpha ; ++i) {
        for(int j = 0 ; j < divBeta ; ++j) {
            mesh.face(index(i + 1, j + 1),
                      index(i, j + 1),
                      index(i, j),
                      index(i + 1, j));
        }
    }

    return mesh;
}

Mesh initKleinBottle(unsigned int divAlpha, unsigned int divBeta) {
    Mesh mesh{GL_TRIANGLES};

    // alpha ∈ [0 ; pi] and beta ∈ [0, 2pi]
    const float stepAlpha = pi() / static_cast<float>(divAlpha), stepBeta = two_pi() / static_cast<float>(divBeta);
    float alpha = 0.0f, beta;

    float x, y, z;

    for(int i = 0 ; i <= divAlpha ; ++i) {
        beta = 0.0f;

        for(int j = 0 ; j <= divBeta ; ++j) {
            x = -2.0f / 15.0f * cosf(alpha) * (
                3.0f * cosf(beta) - 30.0f * sinf(alpha)
                + 90.0f * powf(cosf(alpha), 4.0f) * sinf(alpha)
                - 60.0f * powf(cosf(alpha), 6.0f) * sinf(alpha)
                + 5.0f * cosf(alpha) * cosf(beta) * sinf(alpha));

            y = 2.0f / 15.0f * (3.0f + 5.0f * cosf(alpha) * sinf(alpha)) * sinf(beta);

            z = -1.0f / 15.0f * sinf(alpha) * (
                3.0f * cosf(beta) - 3.0f * powf(cosf(alpha), 2.0f) * cosf(beta)
                -48.0f * powf(cosf(alpha), 4.0f) * cosf(beta)
                +48.0f * powf(cosf(alpha), 6.0f) * cosf(beta)
                -60.0f * sinf(alpha) + 5.0f * cosf(alpha) * cosf(beta) * sinf(alpha)
                -5.0f * powf(cosf(alpha), 3.0f) * cosf(beta) * sinf(alpha)
                -80.0f * powf(cosf(alpha), 5.0f) * cosf(beta) * sinf(alpha)
                +80.0f * powf(cosf(alpha), 7.0f) * cosf(beta) * sinf(alpha));

            mesh.position(x, y, z);

            beta += stepBeta;
        }

        alpha += stepAlpha;
    }

    auto index = [&](int i, int j) -> unsigned {
        return j + i * (divBeta + 1);
    };

    for(int i = 0 ; i < divAlpha ; ++i) {
        for(int j = 0 ; j < divBeta ; ++j) {
            mesh.face(index(i + 1, j + 1),
                      index(i, j + 1),
                      index(i, j),
                      index(i + 1, j));
        }
    }

    return mesh;
}

Mesh initTube(const Point& P0, const Point& P1, const Point& P2, const Point& P3, float radius, unsigned divCurve, unsigned divDisks) {
    Mesh mesh{GL_TRIANGLES};

    // t ∈ [0 ; 1]
    const float stepCurve = 1.f / static_cast<float>(divCurve);
    float t = 0;

    // alpha ∈ [0 ; 2pi]
    const float stepDisk = two_pi() / static_cast<float>(divDisks);
    float alpha;

    Matrix4 rotation;

    Point curve1, curve2, curve3;
    std::vector<Vector> normals;

    normals.push_back(cross(bezierCurve(P0, P1, P2, P3, stepCurve) - P0, Vector{0, 1, 0}));

    if(length(normals[0]) <= 0.00001f) {
        normals[0] = cross(bezierCurve(P0, P1, P2, P3, stepCurve) - P0, Vector{0, 0, 1});
    }

    normals[0] = normalize(normals[0]);

    for(int i = 0 ; i <= divDisks ; ++i) {
        alpha = 0;

        curve1 = bezierCurve(P0, P1, P2, P3, t);
        curve2 = bezierCurve(P0, P1, P2, P3, t + stepCurve);
        curve3 = bezierCurve(P0, P1, P2, P3, t + 2.f * stepCurve);

        rotation = rotate(curve2 - curve1, curve3 - curve2);
        normals.push_back(rotation * normals[normals.size() - 1]);

        for(int j = 0 ; j <= divCurve ; ++j) {
            mesh.normal(normalize(rotate(alpha, curve1 - curve2) * normals[normals.size() - 2]));
            mesh.position(curve1 + radius * mesh.getNormals()->at(mesh.getNormals()->size() - 1));

            alpha += stepDisk;
        }

        t += stepCurve;
    }

    auto index = [&](int i, int j) -> unsigned {
        return j + i * (divCurve + 1);
    };

    for(int i = 0 ; i < divDisks ; ++i) {
        for(int j = 0 ; j < divCurve ; ++j) {
            mesh.face(index(i + 1, j + 1),
                      index(i + 1, j),
                      index(i, j),
                      index(i, j + 1));
        }
    }

    return mesh;
}