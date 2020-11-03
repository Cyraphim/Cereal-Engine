#ifndef APP_H
#define APP_H

#include <SDL.h>
#include <glad/glad.h>
#include <iostream>
#include <vector>

#include "Settings.h"
#include "Shader.h"
#include "Mesh.h"
#include "Loader.h"
#include "ECS.h"
#include "Input.h"
#include "Movement.h"
#include "TIme.h"
#include "Camera.h"

struct Application
{
	static SDL_Window* _window;
	static SDL_GLContext _context;
	static bool _isRunning;

	static void Init();
	static void Run();
	
	static void Input();
	static void Update();
	static void Render();

	static void Close();

	static std::vector<Entity*> gameobjects;
	static Camera* mainCamera;
};

#endif