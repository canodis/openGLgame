#version 330 core

out vec4 FragColor;

in vec4 vertexColor;
in vec4 worldPos;
uniform sampler2D textureSampler;
uniform vec2 lightPosition;
uniform float lightInstensity;
in vec2 texCoords;

void main()
{
    vec4 textureColor = texture(textureSampler, texCoords);
    float distance = length(worldPos.xy - lightPosition);
    float attenuation = 1.0 / (1.0 + distance * lightInstensity);
    FragColor = textureColor * vertexColor * attenuation;
}
