#pragma once
#include "MenuIntro.h"
#include "MenuManager.h"
#include "LevelManager.h"
#include "Camera.h"
#include "Player.h"
#include "HUD.h"
#include "Credits.h"
#include "SoundManager.h"
class Core;

class Game
{
public:
	enum class WindowState
	{
		intro,
		menu,
		credits,
		game
	};


	explicit Game(const Window& window, Core& core);
	Game(const Game& other) = default;
	Game& operator=(const Game& other) = default;
	~Game();

	void Update(float elapsedSec);
	void Draw() const;
	void DrawLevels() const;
	void FullScreenOn() const;
	void FullScreenOff() const;
	void VsyncOn() const;
	void VsyncOff() const;

	// Event handling
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e) const;
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& e);
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e);
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) const;
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) const;

	// Additional Functions
	void DrawWindowStates() const;
	void UpdateWindowStates(float elapsedSec);
	void SetState(WindowState state);

	static float m_CamX;
	static float m_CamY;
private:
	// DATA MEMBERS
	WindowState m_WindowState = WindowState::intro;
	Window m_Window;
	MenuIntro m_MenuIntro;
	Camera m_Camera;
	Core& m_Core;
	SoundManager m_SoundManager;


	bool m_IsStopped{false};
	Point2f m_MousePosition;

	// FUNCTIONS
	void Initialize();
	void Cleanup() const;
	void ClearBackground() const;


	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<LevelManager> m_pLevelManager;
	std::shared_ptr<MenuManager> m_pMenuManager;
	Credits m_Credits;
	HUD m_Hud;
};
