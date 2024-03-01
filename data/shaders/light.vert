#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 2) in vec4 aColor;

uniform mat4 u_model;
uniform mat4 u_model_inverse;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    vec4 FragPos = u_model * vec4(aPosition, 1.0);

    gl_Position = u_projection * u_view * FragPos;
}