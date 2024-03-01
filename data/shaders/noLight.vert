#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec4 aColor;

out vec4 Color;

uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    Color = aColor;

    gl_Position = u_projection * u_view * vec4(aPosition, 1.0);
}