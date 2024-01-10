#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
uniform sampler2D textureSampler;
in vec2 texCoords;

void main()
{
    vec4 textureColor = texture(textureSampler, texCoords);
    FragColor = textureColor * vertexColor;
}
