#version 330 core

in vec4 vertexColor;
in vec3 norm;
in vec2 tex_cord;

out vec4 FragColor;

uniform vec3 directional_light = vec3(0.0, 0.5, 0.5);
uniform float ambient_light = 0.1;

uniform sampler2D my_texture;

void main()
{
    float dot_prod = max(dot(norm, directional_light), ambient_light);

    FragColor = texture(my_texture, tex_cord) * vertexColor * dot_prod;
};