#version 330 core

layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aTexCoord;

out vec3 FragPos;
out vec3 Normal;
out vec4 Color;
out vec2 TexCoord;

uniform mat4 u_model;
uniform mat4 u_model_inverse;
uniform mat4 u_view;
uniform mat4 u_projection;

void main() {
    FragPos = vec3(u_model * vec4(aPosition, 1.0));
    Normal = vec3(u_model_inverse * vec4(aNormal, 1.0));
    Color = aColor;
    TexCoord = aTexCoord;

    gl_Position = u_projection * u_view * vec4(FragPos, 1.0);
}