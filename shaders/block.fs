#version 330 core
out vec4 color;

in vec2 UV;
in float brightness;

uniform sampler2D textureSampler;

void main()
{
    vec4 outColour = texture(textureSampler, UV) * brightness;
    if(outColour.a < 0.1)
        discard;
    color = outColour;
}