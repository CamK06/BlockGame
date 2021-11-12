// The method of doing fog here is taken from jdah's minecraft-weekend project:
// https://github.com/jdah/minecraft-weekend

#version 330 core
out vec4 color;

in vec2 UV;
in float brightness;
in vec3 camPos;

uniform sampler2D textureSampler;

const vec4 fogColour = vec4(0, 0.5, 0.8, 1.0);
const float fogNear = (16 * 16) - 24;
const float fogFar = (16 * 16 ) - 12;

void main()
{
    vec4 outColour = texture(textureSampler, UV) * brightness;
    if(outColour.a < 0.1)
        discard;
    color = outColour;

    float fog = smoothstep(fogNear, fogFar, length(camPos));
    color = mix(color, fogColour, fog);
}