#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in mat4 instanceMtx;

out vec4 vertexColor;
out vec2 texCoords;

uniform mat4 mtxTransform;
uniform vec4 objColor;
uniform mat4 viewMatrix;

void main()
{
    gl_Position = viewMatrix * instanceMtx * mtxTransform * vec4(aPos, 0.0f, 1.0);
    vertexColor = objColor;
    texCoords = aTexCoord;
}