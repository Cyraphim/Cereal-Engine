#include "Application.h"

SDL_Window* Application::_window = NULL;
SDL_GLContext Application::_context = NULL;
bool Application::_isRunning = NULL;
std::vector<Entity*> Application::gameobjects = {};
Camera* Application::mainCamera = NULL;

void Application::Init()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
		return;
	}

	_window = SDL_CreateWindow(Settings::title.c_str(), 
	SDL_WINDOWPOS_UNDEFINED, 
	SDL_WINDOWPOS_UNDEFINED, 
	Settings::width, 
	Settings::height, 
	SDL_WINDOW_OPENGL);

	if(!_window)
	{
		std::cout << "Could not create window: " << SDL_GetError() << std::endl;
		return;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	_context = SDL_GL_CreateContext(_window);
	if(!_context)
	{
		std::cout << "OpenGL Context was not created: " << SDL_GetError() << std::endl;
		return;
	}

	if(SDL_GL_SetSwapInterval(1) < 0)
	{
		std::cout << "Failed to set vSync: " << SDL_GetError() << std::endl;
		return;
	}
	if(!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress))
	{
		std::cout << "OpenGL could not be initailized" << std::endl;
		return;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	glClearColor(0.05f, 0.1f,0.15f,0.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	_isRunning = true;

	// TODO: RELOCATE THIS WHEN YOU MAKE A SCENE MANAGEMENT SYSTEM
	auto potTea = new Entity();
	potTea->_name = "POTTEA";
	potTea->AddComponent<Mesh>(Loader::Instance()->LoadMesh("Resources/Meshes/cube.obj"));
	
	auto _camera = new Entity();
	_camera->_name = "CAMERA";
	_camera->AddComponent<Movement>();
	_camera->AddComponent<Transform>()->position = glm::vec3(0,0,-3);
	mainCamera = _camera->AddComponent<Camera>();
	potTea->GetComponent<Mesh>()->main_camera = mainCamera;
	potTea->GetComponent<Mesh>()->AddTexture("Resources\\Textures\\wall.jpg");
	gameobjects.push_back(potTea);
	gameobjects.push_back(_camera);
	
	
	Application::Run();
}

void Application::Run()
{
	SDL_Event e;

	for (auto g : gameobjects)
	{
		g->Start();
		std::cout << (char)26 << g->_name << std::endl;
		g->ListAllComponents();
	}

	while(_isRunning)
	{
		Time::SetTime();
		while(SDL_PollEvent(&e))
		{
			switch(e.type)
			{
				case SDL_QUIT:
					_isRunning = false;
					break;
			}
		}
		// ESCAPE QUITS THE PROGRAM
		// TODO: REMOVE THIS IS FINAL
		if(Input::Instance()->GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			_isRunning = false;
		}

		Input::Instance()->Update();
		Application::Update();
		Application::Render();
		Input::Instance()->prevUpdate();
		Time::SetDeltaTime();
	}

	Application::Close();
}


void Application::Update()
{
	for (auto g : gameobjects)
	{
		g->Update();
	}
}

void Application::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto g : gameobjects)
	{
		g->Draw();
	}

	SDL_GL_SwapWindow(_window);

}

void Application::Close()
{
	SDL_DestroyWindow(_window);
	SDL_GL_DeleteContext(_context);
	//IMG_Quit();
	SDL_Quit();
}
