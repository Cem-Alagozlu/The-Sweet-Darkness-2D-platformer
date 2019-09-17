#pragma once
#include "Texture.h"
#include "Game.h"
#include "LevelManager.h"
#include <memory>

class MenuStory
{
public:
	MenuStory(MenuManager& manager, Game& pGame, LevelManager& levelManager);
	MenuStory(const MenuStory&) = delete;
	MenuStory& operator=(const MenuStory&) = delete;
	~MenuStory() = default;

	void Draw() const;

	void MouseMoved(const Point2f& mousePos);
	void MouseClick(const SDL_MouseButtonEvent& e);

private:
	Point2f m_MousePos;
	int m_Image{};
	LevelManager& m_LevelManager;

	std::vector<std::unique_ptr<Texture>> m_pStoryTextures;
	Game& m_Game;
	MenuManager& m_Manager;
	std::shared_ptr<Mix_Chunk> m_pBirds;
	std::shared_ptr<Mix_Chunk> m_pWind;
};
