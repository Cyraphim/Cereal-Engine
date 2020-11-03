#pragma once

#include "ECS.h"
#include "Transform.h"
#include "Settings.h"

struct Camera : Component
{
	private:
		Transform* transform;
	public:
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

		
		glm::mat4 GetViewMatrix()
		{
			return perspective * glm::lookAt(transform->position, transform->position + forward, up);
		}
};

