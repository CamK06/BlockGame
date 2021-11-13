#version 330 core

in vec2 UV;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, UV).r);
    if(sampled.w < 0.5)
        discard;
    color = vec4(textColor, 1.0) * sampled;
}