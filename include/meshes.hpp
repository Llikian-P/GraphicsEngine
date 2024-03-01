/******************************************************************************************************
 * @file  meshes.hpp
 * @brief
 ******************************************************************************************************/

#pragma once

#include <glad/glad.h>

#include "Mesh.hpp"

#define BASE_DIV 32
#define BASE_DIV_HALF 16

/**
 * @brief Creates a Mesh representing the three unit axis (X in red, Y in green, Z in blue)
 * @param length Length of the axis
 */
Mesh initAxis(float length = 1.0f);

/**
 * @brief Creates a Mesh representing a sizeX by sizeZ grid divided in 1 by 1 squares
 * @param sizeX Length in the x direction
 * @param sizeZ Length in the z direction
 */
Mesh initGrid(int sizeX = 5, int sizeZ = 5);

/**
 * @brief Creates a cube with sides of size 2
 */
Mesh initCube();

/**
 * @brief Creates a disk of radius 1
 * @param div Number of triangles
 */
Mesh initDisk(unsigned div = BASE_DIV);

/**
 * @brief Creates a cylinder of height 2 with its bottom at y = -1
 * @param div Number of sides
 */
Mesh initCylinder(unsigned div = BASE_DIV);

/**
 * @brief Creates a sphere of radius 1
 * @param divAlpha Number of vertical circles
 * @param divBeta Number of horizontal circles
 */
Mesh initSphere(unsigned divAlpha = BASE_DIV_HALF, unsigned divBeta = BASE_DIV);

/**
 * @brief Creates a cone with the base at y = 0 and of radius 1 and the top at (0, 1, 0)
 * @param div
 */
Mesh initCone(unsigned div = BASE_DIV);

/**
 * @brief Creates a torus
 * @param R Distance between the center of the tube and the center of the torus
 * @param r Radius of the tube
 * @param divAlpha Number of vertical circles
 * @param divBeta Number of horizontal circles
 */
Mesh initTorus(float R = 1.0f, float r = 0.25f, unsigned divAlpha = BASE_DIV_HALF, unsigned divBeta = BASE_DIV);

Mesh initKleinBottle(unsigned divAlpha = BASE_DIV_HALF, unsigned divBeta = BASE_DIV);

///**
// * @brief Creates half a torus that only has half of its horizontal circles (like if you cut a donut in the middle)
// * @param R Distance between the center of the tube and the center of the torus
// * @param r Radius of the tube
// * @param divAlpha Number of vertical circles
// * @param divBeta Twice the number of horizontal circles
// */
//Mesh initHalfTorus(float R = 1.0f, float r = 0.25f, unsigned divAlpha = BASE_DIV_HALF, unsigned divBeta = BASE_DIV);
//
///**
// * @brief Creates a billboard using quads with sides of size 2
// * @param div Number of quads
// */
//Mesh initTree(unsigned div = 4);
//
///**
// * @brief Creates a cubemap with sides of size 2
// */
//Mesh initCubemap();
//
///**
// * @brief Creates a Mesh representing a Bezier curve
// * @param P0 Start point
// * @param P1, P2 Control points
// * @param P3 End point
// * @param div Number of points on the curve
// */
Mesh initCurve(const Point& P0, const Point& P1, const Point& P2, const Point& P3, unsigned div = BASE_DIV);

/**
 * @brief Creates a tube by moving circles along a Bezier curve
 * @param P0 Start point
 * @param P1, P2 Control points
 * @param P3 End point
 * @param radius Radius of the tube
 * @param divCurve Number of circles along the curve
 * @param divDisks Number of points in each circle
 */
Mesh initTube(const Point& P0, const Point& P1, const Point& P2, const Point& P3, float radius = 1.0f, unsigned divCurve = BASE_DIV, unsigned divDisks = BASE_DIV);

///**
// * @brief Creates a Mesh using a silhouette of points and rotating it around the Y axis
// * @param silhouette Holds an array of points representing the silhouette of the shape
// * @param div Number of divisions around the y axis
// */
//Mesh initRevolution(const std::vector<Point>& silhouette, unsigned div = BASE_DIV);
//
///**
// * @brief Creates a superellipse shape of radius 1
// * @source https://en.wikipedia.org/wiki/Superellipse
// * @param n Positive number that controls the "squareness" of the shape
// * @param div Number of triangles
// */
//Mesh initSuperellipse(float n = 4.0f, unsigned div = BASE_DIV);
//
///**
// * @brief Creates a superellipsoid shape of radius 1
// * @source https://en.wikipedia.org/wiki/Superellipsoid
// * @param e1, e2 Positive numbers that control the "squareness" of the shape
// * @param divAlpha Number of vertical superellipses
// * @param divBeta Number of horizontal superellipses
// */
//Mesh initSuperellipsoid(float e1 = 0.5f, float e2 = 0.5f, unsigned divAlpha = BASE_DIV, unsigned divBeta = BASE_DIV);
//
///**
// * @brief Creates a hollow cylinder of height 2 with its base at y = -1
// * @param radiusMajor Radius of the bigger cylinder
// * @param radiusMinor Radius of the smaller cylinder
// * @param div Number of sides
// */
//Mesh initHollowCylinder(float radiusMajor = 1.0f, float radiusMinor = 0.5f, unsigned div = BASE_DIV);