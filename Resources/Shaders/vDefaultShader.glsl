#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexture;

uniform mat4 model;
uniform mat4 view;

out vec2 TexCoords;
out vec3 Position;
out vec3 Normal;
out vec3 FragmentPosition;

void main()
{
        gl_Position = view * model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
        FragmentPosition = vec3(model * vec4(aPos, 1.0));
        TexCoords = aTexture;
        Position = aPos;
        Normal = aNormal;

}
