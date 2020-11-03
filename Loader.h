#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

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
		
		Mesh* LoadMesh(std::string filePath)
		{
			std::vector<glm::vec3> vert;
			std::vector<unsigned int> vertIndices;

			std::stringstream ss;
			std::ifstream in_file(filePath);
			std::string line = "";
			std::string prefix = "";

			if (!in_file.is_open())
			{
				std::cout << "ERROR: Could not open file => " << filePath << std::endl;
			}

			while (std::getline(in_file, line))
			{
				ss.clear();
				ss.str(line);
				ss >> prefix;

				if (line == "" || prefix == "#")
				{
					continue;
				}

				if (prefix == "v")
				{
					glm::vec3 temp;
					ss >> temp.x >> temp.y >> temp.z;
					temp.x /= 2; temp.y /= 2; temp.z /= 2;
					vert.push_back(temp);
				}
				if (prefix == "f")
				{
					GLuint x, y, z;
					ss >> x >> y >> z;
					x -= 1;
					y -= 1;
					z -= 1;

					vertIndices.push_back(x);
					vertIndices.push_back(y);
					vertIndices.push_back(z);
					
				}
			}

			auto m = new Mesh();
			m->AddVI(vert,vertIndices);
			m->AddShader();
			return m;
		}

};

