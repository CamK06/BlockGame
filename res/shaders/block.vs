#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in float aBrightness;

out vec2 UV;
out float brightness;
out vec3 camPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
    UV = aUV;
    brightness = aBrightness;
    camPos = ((view * model) * vec4(aPos, 1.0)).xyz;
} 