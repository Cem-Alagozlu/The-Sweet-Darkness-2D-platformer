#include "stdafx.h"
#include "Core.h"

#include <iostream>
#include <algorithm>

#include "Game.h"

Core::Core(const Window& window)
	: m_Window{window}
	  , m_Initialized{false}
{
	Initialize();
}

Core::~Core()
{
	Cleanup();
}

void Core::Initialize()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Core::Initialize( ), error when calling SDL_Init: " << SDL_GetError() << std::endl;
		return;
	}

	// Use OpenGL 2.1
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	// Create window
	m_pWindow = SDL_CreateWindow(
		m_Window.title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		int(m_Window.width),
		int(m_Window.height),
		SDL_WINDOW_OPENGL);
	if (m_pWindow == nullptr)
	{
		std::cerr << "Core::Initialize( ), error when calling SDL_CreateWindow: " << SDL_GetError() << std::endl;
		return;
	}

	// Create OpenGL context 
	m_pContext = SDL_GL_CreateContext(m_pWindow);
	if (m_pContext == nullptr)
	{
		std::cerr << "Core::Initialize( ), error when calling SDL_GL_CreateContext: " << SDL_GetError() << std::endl;
		return;
	}

	// Set the swap interval for the current OpenGL context,
	// synchronize it with the vertical retrace
	if (m_Window.isVSyncOn)
	{
		if (SDL_GL_SetSwapInterval(1) < 0)
		{
			std::cerr << "Core::Initialize( ), error when calling SDL_GL_SetSwapInterval: " << SDL_GetError() << std::endl;
			return;
		}
	}

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	gluOrtho2D(0, m_Window.width, 0, m_Window.height); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangular region of the window where the image is drawn.
	glViewport(0, 0, int(m_Window.width), int(m_Window.height));

	// Set the Modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cerr << "Core::Initialize( ), error when calling IMG_Init: " << IMG_GetError() << std::endl;
		return;
	}

	// Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		std::cerr << "Core::Initialize( ), error when calling TTF_Init: " << TTF_GetError() << std::endl;
		return;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cerr << "Core::Initialize( ), error when calling Mix_OpenAudio: " << Mix_GetError() << std::endl;
		return;
	}

	m_Initialized = true;
}

void Core::Run()
{
	if (!m_Initialized)
	{
		std::cerr << "Core::Run( ), Core not correctly initialized, unable to run the game\n";
		std::cin.get();
		return;
	}

	// Create the Game object
	Game game{m_Window,*this};

	// Main loop flag
	bool quit{false};

	// Set start time
	std::chrono::high_resolution_clock::time_point m_T1 = std::chrono::high_resolution_clock::now();

	//The event loop
	SDL_Event e{};
	while (!quit)
	{
		// Poll next event from queue
		while (SDL_PollEvent(&e) != 0)
		{
			// Handle the polled event
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				game.ProcessKeyDownEvent(e.key);
				break;
			case SDL_KEYUP:
				game.ProcessKeyUpEvent(e.key);
				break;
			case SDL_MOUSEMOTION:
				game.ProcessMouseMotionEvent(e.motion);
				break;
			case SDL_MOUSEBUTTONDOWN:
				game.ProcessMouseDownEvent(e.button);
				break;
			case SDL_MOUSEBUTTONUP:
				game.ProcessMouseUpEvent(e.button);
				break;
			default: ;
			}
		}
		if (!quit)
		{
			// Calculate elapsed time
			// Get current time
			std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
			// Calculate elapsed time
			std::chrono::duration<float> timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - m_T1);
			float elapsedTime = timeSpan.count();
			// Update current time
			m_T1 = t2;
			// Prevent jumps in time caused by break points
			const float maxElapsedTime{0.1f};
			elapsedTime = std::min(elapsedTime, maxElapsedTime);

			// Call the Game object 's Update function, using time in seconds (!)
			game.Update(elapsedTime);

			// Draw in the back buffer
			game.Draw();

			// Update screen: swap back and front buffer
			SDL_GL_SwapWindow(m_pWindow);
		}
	}
}

void Core::SetFullScreen()
{
	if (m_IsFullScreen)
	{
		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_BORDERLESS);
		m_IsFullScreen = false;
	}
	else
	{
		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN);
		m_IsFullScreen = true;
	}
}

void Core::SetFullScreenOn()
{
	SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_FULLSCREEN);
	m_IsFullScreen = true;
}

void Core::SetFullScreenOff()
{
	if (m_IsFullScreen)
	{
		SDL_SetWindowFullscreen(m_pWindow, SDL_WINDOW_BORDERLESS);
		m_IsFullScreen = false;
	}
}

void Core::ToggleVsyncOn()
{
		m_Window.isVSyncOn = true;
		SDL_GL_SetSwapInterval(1);
}

void Core::ToggleVsyncOff()
{
	m_Window.isVSyncOn = false;
	SDL_GL_SetSwapInterval(0);
}

void Core::Cleanup()
{
	SDL_GL_DeleteContext(m_pContext);

	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;

	//Quit SDL subsystems
	Mix_CloseAudio();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
