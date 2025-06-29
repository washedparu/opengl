#version 330 core

layout(location = 0) out vec4 color;

in vec2 vTexCoord;

uniform sampler2D uTexture;
uniform vec2 uOffset;

void main()
{
  vec4 texColor = texture(uTexture, vTexCoord + uOffset);
  color = texColor;
}