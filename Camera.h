#pragma once

#include "ECS.h"
#include "Transform.h"
#include "Settings.h"

struct Camera : Component
{
	private:
		// Position and rotation of the camera
		Transform* transform;
	public:
		// The direction the camera is pointing
		glm::vec3 forward;

		glm::vec3 up;
		glm::mat4 perspective;

		void Start()
		{
			// YAW:PITCH:ROLL :: Y:X:Z

			if (!entity->HasComponent<Transform>())
			{
				entity->AddComponent<Transform>();
			}

			transform = entity->GetComponent<Transform>();
			
			perspective = glm::perspective(Settings::FOV, ((float)Settings::width)/((float)Settings::height), 0.01f, 1000.0f);

			forward = glm::vec3(0, 0, 1);
			up = glm::vec3(0, 1, 0);
		}

		
		// THIS CODE DOES NOT ACCOUNT FOR ROLL
		// TODO: FIGURE IT OUT, BITCH
		glm::mat4 GetViewMatrix()
		{
			auto Forward = forward * glm::mat3(glm::rotate(glm::mat4(1), transform->rotation.x, glm::vec3(0, 1, 0)));
			Forward = Forward * glm::mat3(glm::rotate(glm::mat4(1), transform->rotation.y, glm::vec3(1, 0, 0)));
					

			auto Right = glm::cross(Forward, up);
			
			auto Up = glm::cross(Right, Forward);

			return perspective * glm::lookAt(transform->position, transform->position + Forward, Up);
		}
};

