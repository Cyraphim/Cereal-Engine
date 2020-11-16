#pragma once

#include <iostream>

#include "Mesh.h"

class Loader
{
	private:
		static Loader* instance;
		Loader()
		{
		}

	public:
		static Loader* Instance()
		{
			if(!instance)
			{
				instance = new Loader();
			}
			return instance;
		}
		
		// LOADS ONLY OBJ FILES
		Mesh* LoadMesh(std::string filePath)
		{
			std::vector<glm::vec3> vert;
			std::vector<unsigned int> vi;

			std::vector<glm::vec2> texture;
			std::vector<unsigned int> ti;

			std::vector<glm::vec3> normal;
			std::vector<unsigned int> ni;


			FILE* meshFile;
			auto error = fopen_s(&meshFile, filePath.c_str(), "r");

			if (error != 0)
			{
				std::cout << "ERROR: Could not open file => " << filePath << std::endl;
			}
			fseek(meshFile, 0L, SEEK_SET);
			while (true)
			{
				char lineHeader[128];
				// read the first word of the line
				int res = fscanf_s(meshFile, "%s", lineHeader, _countof(lineHeader));
				if (res == EOF)
					break;

				if (strcmp(lineHeader, "v") == 0)
				{
					glm::vec3 temp;
					fscanf_s(meshFile, "%f %f %f\n", &(temp.x), &(temp.y), &(temp.z));
					vert.push_back(temp);
				}
				else if (strcmp(lineHeader, "vt") == 0)
				{
					glm::vec2 temp;
					fscanf_s(meshFile, "%f %f\n", &(temp.x), &(temp.y));
					texture.push_back(temp);
				}
				else if (strcmp(lineHeader, "vn") == 0)
				{
					glm::vec3 temp;
					fscanf_s(meshFile, "%f %f %f\n", &(temp.x), &(temp.y), &(temp.z));
					normal.push_back(temp);
				}

				else if (strcmp(lineHeader, "f") == 0)
				{
					GLuint xv, yv, zv;
					GLuint xt, yt, zt;
					GLuint xn, yn, zn;
					int matches = fscanf_s(meshFile, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &xv, &xt, &xn, &yv, &yt, &yn, &zv, &zt, &zn);
					
					if(matches != 9)
					{
						std::cout << "IMPORT ERROR: " << filePath << " (Could not get all indices)" << std::endl;
						return NULL;
					}

					xv -= 1;
					yv -= 1;
					zv -= 1;

					xt -= 1;
					yt -= 1;
					zt -= 1;

					xn -= 1;
					yn -= 1;
					zn -= 1;

					vi.push_back(xv);
					vi.push_back(yv);
					vi.push_back(zv);

					ni.push_back(xn);
					ni.push_back(yn);
					ni.push_back(zn);

					ti.push_back(xt);
					ti.push_back(yt);
					ti.push_back(zt);
				}
			}

			std::vector<unsigned int> indices;
			std::vector<Vertex> vertices;

			for (unsigned int i = 0; i < vi.size(); i++)
			{
				Vertex v;

				v.position = vert[vi[i]];
				v.normal = normal[ni[i]];
				v.texture = texture[ti[i]];

				indices.push_back(i);

				vertices.push_back(v);
			}

			auto m = new Mesh();
			m->AddVI(vertices, indices);
			m->AddShader();
			return m;
		}

};

