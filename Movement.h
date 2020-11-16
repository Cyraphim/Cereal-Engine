#pragma once

#include "ECS.h"
#include "Transform.h"
#include "Input.h"
#include "Time.h"

struct Movement : Component
{
	private:
		Transform* transform;
	public:

	void Start()
	{
		if(!entity->HasComponent<Transform>())
		{
			entity->AddComponent<Transform>();
		}

		transform = entity->GetComponent<Transform>();
	}
	
	void Update()
	{
		if (Input::Instance()->GetKeyHeld(SDL_SCANCODE_W))
		{
			transform->position.z += 1 * Time::DeltaTime();
		}
		if (Input::Instance()->GetKeyHeld(SDL_SCANCODE_S))
		{
			transform->position.z -= 1 * Time::DeltaTime();
		}
		if (Input::Instance()->GetKeyHeld(SDL_SCANCODE_A))
		{
			transform->position.x -= 1 * Time::DeltaTime();
		}
		if (Input::Instance()->GetKeyHeld(SDL_SCANCODE_D))
		{
			transform->position.x += 1 * Time::DeltaTime();
		}

		if (Input::Instance()->GetKeyHeld(SDL_SCANCODE_Q))
		{
			transform->position.y += 1 * Time::DeltaTime();
		}
		if (Input::Instance()->GetKeyHeld(SDL_SCANCODE_E))
		{
			transform->position.y -= 1 * Time::DeltaTime();
		}

		if (Input::Instance()->GetKeyHeld(SDL_SCANCODE_L))
		{
			transform->rotation.x += 1 * Time::DeltaTime();
		}
		if (Input::Instance()->GetKeyHeld(SDL_SCANCODE_J))
		{
			transform->rotation.x -= 1 * Time::DeltaTime();
		}

		if (Input::Instance()->GetKeyHeld(SDL_SCANCODE_I))
		{
			transform->rotation.y += 1 * Time::DeltaTime();
		}
		if (Input::Instance()->GetKeyHeld(SDL_SCANCODE_K))
		{
			transform->rotation.y -= 1 * Time::DeltaTime();
		}
	}
};

