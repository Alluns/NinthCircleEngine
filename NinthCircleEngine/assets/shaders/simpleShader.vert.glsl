#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

out vec4 vertexColor;
out vec3 norm;
out vec2 tex_cord;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;
uniform vec3 color;

void main()
{
   gl_Position = projection * view * transform * vec4(position, 1.0);
   vertexColor = vec4(color, 1.0);

   norm = normal;
    tex_cord = uv;
};