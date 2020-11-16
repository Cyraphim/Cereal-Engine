#ifndef APP_H
#define APP_H

#include <SDL.h>
#include <SDL_image.h>
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

	// Init will initialize all the required libraries
	static void Init();
	// Run will start the game loop
	static void Run();
	
	// Update the data of all the gameobjects/entities
	static void Update();
	// Draw all the gameobjects/entities
	static void Render();

	// Close out all the libraries
	static void Close();

	// Basic Entity List
	// TODO: Change this to a better/ more efficient data structure
	static std::vector<Entity*> gameobjects;
	// Main Camera, POV of window
	// TODO: Find a better place to keep this
	static Camera* mainCamera;
};

#endif