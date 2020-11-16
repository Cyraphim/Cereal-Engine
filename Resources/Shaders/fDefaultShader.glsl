#version 460 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Position;

uniform sampler2D bTexture;

void main()
{
      FragColor = texture(bTexture, TexCoords);
}