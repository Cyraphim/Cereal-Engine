#pragma once

#include "ECS.h"
#include "glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"

struct Transform : Component
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;

	Transform()
	{
		position = glm::vec3(0, 0, 0);
		rotation = glm::vec3(0, 0, 0);
		scale = glm::vec3(1, 1, 1);
	}

	glm::mat4 GetTransformationMatrix()
	{
		glm::mat4 toRet(1);

		toRet = glm::translate(toRet, position);
		toRet = glm::rotate(toRet, glm::radians(rotation.x), glm::vec3(1, 0, 0));
		toRet = glm::rotate(toRet, glm::radians(rotation.y), glm::vec3(0, 1, 0));
		toRet = glm::rotate(toRet, glm::radians(rotation.z), glm::vec3(0, 0, 1));
		toRet = glm::scale(toRet, scale);

		return toRet;
	}

};

