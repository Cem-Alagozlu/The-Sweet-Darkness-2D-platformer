#pragma once
#include <chrono>

class Core
{
public:
	explicit Core(const Window& window);
	Core(const Core& other) = delete;
	Core& operator=(const Core& other) = delete;
	~Core();

	void Run();
	void SetFullScreen();
	void SetFullScreenOn();
	void SetFullScreenOff();
	void ToggleVsyncOn();
	void ToggleVsyncOff();
private:
	// DATA MEMBERS
	// The window properties
	Window m_Window;
	// The window we render to
	SDL_Window* m_pWindow{};
	// OpenGL context
	SDL_GLContext m_pContext{};
	// The time keeper
	std::chrono::high_resolution_clock::time_point m_T1;
	// Init info
	bool m_Initialized;
	bool m_IsFullScreen{false};

	// FUNCTIONS
	void Initialize();
	void Cleanup();
};
