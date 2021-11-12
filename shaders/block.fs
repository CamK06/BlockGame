#version 330 core
out vec4 color;

in vec2 UV;
in float brightness;

uniform sampler2D textureSampler;

void main()
{
    color = texture(textureSampler, UV) * brightness;
}