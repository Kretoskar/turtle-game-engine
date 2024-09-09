#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 texUV;

uniform sampler2D diffuseMap;

void main()
{
    FragColor = texture(diffuseMap, texUV);
}