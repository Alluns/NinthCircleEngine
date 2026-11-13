#version 330 core

in vec4 vertexColor;
in vec3 norm;

out vec4 FragColor;

uniform vec3 directional_light = vec3(0.0f, 0.5f, 0.5f);
uniform float ambient_light = 0.1f;

void main()
{
    float dot_prod = max(dot(norm, directional_light), ambient_light);

    FragColor = vertexColor * dot_prod;
};