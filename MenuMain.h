#pragma once
#include "Texture.h"
#include "MenuManager.h"

class Game;

class MenuMain
{
public:

	MenuMain(MenuManager& manager);
	MenuMain(const MenuMain&) = delete;
	MenuMain& operator=(const MenuMain&) = delete;
	~MenuMain() = default;

	void Draw() const;

	void MouseMoved(const Point2f& mousePos);
	void MouseClick(const SDL_MouseButtonEvent& e) const;

private:
	std::vector<std::unique_ptr<Texture>> m_pMainMenuText;
	MenuManager& m_Manager;
	Point2f m_MousePos;
	std::shared_ptr<Mix_Music> m_pStoryMusic;
};
