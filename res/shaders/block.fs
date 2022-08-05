// The method of doing fog here is taken from jdah's minecraft-weekend project:
// https://github.com/jdah/minecraft-weekend

#version 330 core
out vec4 color;

in vec2 UV;
in float brightness;
in vec3 camPos;

uniform sampler2D textureSampler;
uniform int renderDistance = 3;

const vec4 fogColour = vec4(0, 0.5, 0.8, 1.0);

void main()
{
    vec4 outColour = texture(textureSampler, UV) * brightness;
    if(outColour.a < 0.1)
        discard;
    color = outColour;

    float fogNear = (16 * (renderDistance+1)) - 24;
    float fogFar = (16 * (renderDistance+1)) - 12;
    float fog = smoothstep(fogNear, fogFar, length(camPos));
    color = mix(color, fogColour, fog);
}