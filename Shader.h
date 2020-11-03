#pragma once

#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm.hpp>


struct Shader
{
	unsigned int ID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use()
	{
		glUseProgram(ID);
	}
	
	void setMat4(const std::string name, glm::mat4 value)
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &value[0][0]);
	}
};

