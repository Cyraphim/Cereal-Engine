#pragma once

#include <SDL.h>

struct Time
{
	private:
	static double deltaTime;
	static Uint32 START;
	static Uint32 END;
	public:
	static void SetTime()
	{
		START = SDL_GetTicks();
	}

	static void SetDeltaTime()
	{
		END = SDL_GetTicks();
		deltaTime = (END - START)/1000.0;
	}

	static double DeltaTime()
	{
		return deltaTime;
	}
};

