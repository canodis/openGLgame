#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec4 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 texCoords;

uniform mat4 mtxTransform;

void main()
{
    gl_Position = mtxTransform * vec4(aPos, 0.0f, 1.0);
    vertexColor = aColor;
    texCoords = aTexCoord;
}
