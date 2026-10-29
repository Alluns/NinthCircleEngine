#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

uniform vec3 aOffset;
uniform vec3 aRotation;
uniform vec3 aScale;
uniform vec3 aColor;

void main()
{
   vec3 scalePos = aPos * aScale;
   vec3 rotPos = vec3(scalePos.x * cos(aRotation.x) - scalePos.y * sin(aRotation.x), scalePos.y * cos(aRotation.x) + scalePos.x * sin(aRotation.x), 1.0f);
   gl_Position = vec4(rotPos + aOffset, 1.0);
   vertexColor = vec4(aColor, 1.0);
};