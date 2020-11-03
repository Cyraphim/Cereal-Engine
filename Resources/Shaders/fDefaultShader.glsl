#version 330 core
out vec4 FragColor;
in vec3 PosA;
void main()
{
   FragColor = vec4(PosA, 1.0f);

}