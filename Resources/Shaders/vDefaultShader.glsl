#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

uniform mat4 model;

out vec2 TexCoords;
out vec3 Position;

void main()
{
        gl_Position = model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
        TexCoords = aTexture;
        Position = aPos;

}
