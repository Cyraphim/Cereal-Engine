#pragma once

#include <glm.hpp>
#include <iostream>
#include <SDL.h>
#include <vector>
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Shader.h"
#include "ECS.h"
#include "Transform.h"
#include "Camera.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;
};

struct Texture
{
	unsigned int id = 0;
	std::string type;
	std::string path;
};

struct Mesh : Component
{
	private:
		// Position, Scale, and Rotation of an object
		Transform* transform;

	public:
		Camera* main_camera;
	Shader* shader;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture *> textures;

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

	void AddVI(std::vector<Vertex> v, std::vector<unsigned int> indices = {})
	{
			
			this->vertices = v;
			this->indices = indices;

			setupMesh();
	}

	void AddTexture(std::string filepath)
	{
		unsigned int TextureID;
		// Generate textures
		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		// Do some settings
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Load the texture into memory
		// TODO: use SDL_Image library
		int width, height, nr;
		auto data = stbi_load(filepath.c_str(), &width, &height, &nr, 0);

		// if the data has been loaded, add it to our texture list
		if(data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			Texture* t = new Texture();
			t->id = TextureID;
			t->path = filepath;
			t->type = " ";

			textures.push_back(t);
			std::cout << "TEXTURE HAS BEEN LOADED" << std::endl;
		}

		stbi_image_free(data);

	}	

	void setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);		

		// Settings for position
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

		// Settings for normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

		// Settings for textures
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texture));

		glBindVertexArray(0);
	}
	
	void Draw()
	{
		shader->setMat4("model", main_camera->GetViewMatrix() * transform->GetTransformationMatrix());
		glBindVertexArray(VAO);

		// Setting all the textures
		for(int i = 0; i < textures.size(); i++)
			{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]->id);
		}

		shader->use();
		
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}
	
};

