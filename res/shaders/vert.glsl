#version 330 core

layout(location = 0) in vec2 aPosition;
layout(location = 1) in vec2 atexCoord;

out vec2 vTexCoord;

void main()
{
    vTexCoord = atexCoord;
    gl_Position = vec4(aPosition, 0.0, 1.0);
}
