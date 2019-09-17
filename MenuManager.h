#pragma once

#include "stdafx.h"
#include "Texture.h"


class Game;
class MenuMain;
class MenuQuit;
class MenuExtra;
class MenuQuit;
class MenuStory;
class LevelManager;

class MenuManager
{
public:
	enum class MenuState
	{
		menuMain,
		menuExtra,
		menuQuit,
		menuStory,
		menuExtraStory,
		menuExtraOptions,
		menuExtraCredits
	};

	MenuManager(Game& game, LevelManager& levelManager);
	MenuManager(const MenuManager&) = delete;
	MenuManager& operator=(const MenuManager&) = delete;
	~MenuManager() = default;

	void Draw() const;
	void Update(float elapsedSec);

	void MouseMoved(const Point2f& mousePos) const;
	void MouseClick(const SDL_MouseButtonEvent& e) const;
	static void SetState(MenuState state);

	void InitializeBackground();
	void UpdateBackground(float elapsedSec);
	void FullScreenOn() const;
	void FullScreenOff() const;
	void VsyncOn() const;
	void VsyncOff() const;


private:
	static MenuState m_MenuState;

	const int m_MenuAmount{300};
	int m_MenuIMGS01{};
	float m_ElapsedTime;
	float m_BackgroundTime;
	int m_Timer02;

	Point2f m_MousePos;

	std::vector<std::unique_ptr<Texture>> m_pMenuImgs;

	Game& m_Game;
	std::shared_ptr<MenuExtra> m_pMenuExtra;
	std::shared_ptr<MenuQuit> m_pMenuQuit;
	std::shared_ptr<MenuMain> m_pMenuMain;
	std::shared_ptr<MenuStory> m_pMenuStory;
};
