#pragma once

#include <glm.hpp>
#include "Shader.h"
#include <iostream>
#include <SDL.h>
#include <vector>
#include "ECS.h"
#include "Transform.h"
#include "Camera.h"


struct Mesh : Component
{
	private:
		Transform* transform;

	public:
		Camera* main_camera;
	Shader* shader;
	std::vector<glm::vec3> vertices;
	std::vector<unsigned int> indices;

	GLuint VBO, VAO, EBO;

	void Start()
	{
		if(entity->HasComponent<Transform>())
		{
		transform = entity->GetComponent<Transform>();
		
		}
		else
		{
			transform = entity->AddComponent<Transform>();
		}
	}

	void AddShader(const char* vShader = "Resources/Shaders/vDefaultShader.glsl", const char* fShader = "Resources/Shaders/fDefaultShader.glsl")
	{
		shader = new Shader(vShader, fShader);
		setupMesh();
	}

	void AddVI(std::vector<glm::vec3> v = {}, std::vector<unsigned int> i = {})
	{
		if (v.size() && i.size())
		{
			indices = i;
			vertices = v;
			setupMesh();
		}
	}

	void setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);		

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,3 * sizeof(float), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	void Draw()
	{
		shader->setMat4("model", main_camera->GetViewMatrix() * transform->GetTransformationMatrix());

		shader->use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	
};

