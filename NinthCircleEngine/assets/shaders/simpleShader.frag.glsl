#version 330 core

in vec4 vertexColor;
in vec3 norm;

out vec4 FragColor;

void main()
{
    FragColor = vec4(norm, 1);
};