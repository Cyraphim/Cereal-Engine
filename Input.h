#pragma once

#include <SDL.h>
#include "Settings.h"
#include "glm.hpp"

enum MOUSE_STATE
{
	LEFT,
	MIDDLE,
	RIGHT,
	FORWARD,
	BACKWARD

};

struct Input
{
	private:
	static Input* instance;
	const Uint8* keyboardState;
	Uint8* prevKeyboardState;
	
	Uint32 mouseState;
	Uint32 prevMouseState;
	
	glm::ivec2 mousePosition;

	Input()
	{
		SDL_PumpEvents();
		keyboardState = SDL_GetKeyboardState(&Settings::numKeys);
		prevKeyboardState = new Uint8[Settings::numKeys];
		memcpy(prevKeyboardState, keyboardState, Settings::numKeys);
	
		mouseState = SDL_GetMouseState(&(mousePosition.x), &(mousePosition.y));
		prevMouseState = mouseState;
	}
	public:

	static Input* Instance()
	{
		if(!instance)
		{
			instance = new Input();
		}

		return instance;
	}

	void Update()
	{
		keyboardState = SDL_GetKeyboardState(NULL);
		mouseState = SDL_GetMouseState(&(mousePosition.x), &(mousePosition.y));

	}

	void prevUpdate()
	{
		memcpy(prevKeyboardState, keyboardState, Settings::numKeys);
		prevMouseState = mouseState;

	}

	bool GetKeyDown(SDL_Scancode key)
	{
		return (!prevKeyboardState[key] && keyboardState[key]);
	}

	bool GetKeyUp(SDL_Scancode key)
	{
		return (prevKeyboardState[key] && !keyboardState[key]);
	}

	bool GetKeyHeld(SDL_Scancode key)
	{
		return (keyboardState[key]);
	}


	bool GetMouseDown(MOUSE_STATE m)
	{
		int mask = 0;

		switch (m)
		{
		case LEFT:
			mask = SDL_BUTTON_LMASK;
			break;

		case MIDDLE:
			mask = SDL_BUTTON_MMASK;
			break;

		case RIGHT:
			mask = SDL_BUTTON_RMASK;
			break;

		case FORWARD:
			mask = SDL_BUTTON_X1MASK;
			break;

		case BACKWARD:
			mask = SDL_BUTTON_X2MASK;
			break;
		}

		return (!(prevMouseState & mask) && (mouseState & mask));
	}

	bool GetMouseUp(MOUSE_STATE m)
	{
		int mask = 0;

		switch (m)
		{
		case LEFT:
			mask = SDL_BUTTON_LMASK;
			break;

		case MIDDLE:
			mask = SDL_BUTTON_MMASK;
			break;

		case RIGHT:
			mask = SDL_BUTTON_RMASK;
			break;

		case FORWARD:
			mask = SDL_BUTTON_X1MASK;
			break;

		case BACKWARD:
			mask = SDL_BUTTON_X2MASK;
			break;
		}

		return ((prevMouseState & mask) && !(mouseState & mask));
	}

	bool GetMouseHeld(MOUSE_STATE m)
	{
		int mask = 0;

		switch (m)
		{
		case LEFT:
			mask = SDL_BUTTON_LMASK;
			break;

		case MIDDLE:
			mask = SDL_BUTTON_MMASK; 
			break;

		case RIGHT:
			mask = SDL_BUTTON_RMASK;
			break;

		case FORWARD:
			mask = SDL_BUTTON_X1MASK;
			break;

		case BACKWARD:
			mask = SDL_BUTTON_X2MASK;
			break;
		}

		return ((mouseState & mask));
	}

	glm::ivec2 GetMousePosition()
	{
		return this->mousePosition;
	}


};

