#version 330 core

layout (location = 0) in vec3 aPos;
uniform mat4 model;
out vec3 PosA;

void main()
{
        gl_Position = model * vec4(aPos.x, aPos.y, aPos.z, 1.0);
        PosA = aPos;
}
