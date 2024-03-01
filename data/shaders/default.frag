#version 330 core

struct Material {
    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
    float shininess;
};

struct Light {
    vec3 position;

    vec4 ambient;
    vec4 diffuse;
    vec4 specular;
};

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec4 Color;
in vec2 TexCoord;

uniform bool u_hasTexture;
uniform sampler2D u_texture;

uniform Light u_light;
uniform Material u_material;
uniform vec3 u_cameraPosition;

void main() {
    // ambient
    vec4 ambient = u_light.ambient * u_material.ambient;

    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(u_light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = u_light.diffuse * (diff * u_material.diffuse);

    // specular
    vec3 viewDir = normalize(u_cameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);
    vec4 specular = u_light.specular * (spec * u_material.specular);

    FragColor = ambient + diffuse + specular;

    if(u_hasTexture) {
        FragColor *= texture(u_texture, TexCoord);
    }
}