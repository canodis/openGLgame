#version 410 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 texCoords;
out vec2 worldPos;

uniform mat4 mtxTransform;
uniform mat4 projMatrix;
uniform vec4 objColor;
uniform mat4 viewMatrix;

void main()
{
    gl_Position = viewMatrix * projMatrix * mtxTransform * vec4(aPos, 0.0f, 1.0);
    vertexColor = objColor;
    texCoords = aTexCoord;
    worldPos = mtxTransform[3].xy + aPos;
}