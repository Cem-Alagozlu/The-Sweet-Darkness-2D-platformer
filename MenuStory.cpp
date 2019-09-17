#include "stdafx.h"
#include "MenuStory.h"
#include <sstream>
#include "Game.h"

MenuStory::MenuStory(MenuManager& manager, Game& game, LevelManager& levelManager)
	: m_LevelManager{levelManager}
	  , m_Game{game}
	  , m_Manager{manager}
{
	for (int idx = 0; idx < 14; ++idx)
	{
		std::stringstream str;
		str << "Resources/Images/Storyline/" << idx + 1 << ".png";
		m_pStoryTextures.push_back(std::make_unique<Texture>(str.str()));
	}
	m_pBirds = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV("Resources/Sound/Sound_Effects/Birds.mp3"), [](Mix_Chunk* track) { Mix_FreeChunk(track); });
}

void MenuStory::Draw() const
{
	m_pStoryTextures[m_Image]->Draw(Rectf{0.0f,0.0f,1280.0f,720.0f});

	std::cout << m_Image << " image " << std::endl;
}

void MenuStory::MouseMoved(const Point2f& mousePos)
{
	m_MousePos = mousePos;
}

void MenuStory::MouseClick(const SDL_MouseButtonEvent& e)
{
	++m_Image;
	if (m_Image >= 13)
	{
		m_Image = 13;

		m_LevelManager.SetCurrentLevel(LevelManager::Level::levelOne);
		m_Game.SetState(Game::WindowState::game);
	}
	if (m_Image == 9)
	{
		Mix_PlayChannel(-1,m_pBirds.get(),0);
	}
}
