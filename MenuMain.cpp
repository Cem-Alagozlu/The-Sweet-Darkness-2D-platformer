#include "stdafx.h"
#include "MenuMain.h"
#include "Game.h"
#include "utils.h"
#include "SoundManager.h"


MenuMain::MenuMain(MenuManager& manager)
	: m_Manager{manager}
{
	m_pMainMenuText.push_back(std::make_unique<Texture>("Play", "Resources/Fonts/Font00.ttf", 60, Color4f{1,1,1,1}));
	m_pMainMenuText.push_back(std::make_unique<Texture>("Extra", "Resources/Fonts/Font00.ttf", 60, Color4f{1,1,1,1}));
	m_pMainMenuText.push_back(std::make_unique<Texture>("Exit", "Resources/Fonts/Font00.ttf", 60, Color4f{1,1,1,1}));
}

void MenuMain::Draw() const
{
	utils::SetColor({0,0,0,0.4f});
	utils::FillRect({515,420,250,70});//first
	utils::FillRect({515,320,250,70});//mid
	utils::FillRect({515,220,250,70});//second
	m_pMainMenuText[0]->Draw({575,420});
	m_pMainMenuText[1]->Draw({565,320});
	m_pMainMenuText[2]->Draw({585,218});

	if (m_MousePos.x >= 515 && m_MousePos.x <= 765)
	{
		if (m_MousePos.y >= 420 && m_MousePos.y <= 490)
		{
			utils::DrawRect({515,420,250,70}, 5.0f);//first
		}
		else if (m_MousePos.y >= 320 && m_MousePos.y <= 390)
		{
			utils::DrawRect({515,320,250,70}, 5.0f);//first
		}
		else if (m_MousePos.y >= 220 && m_MousePos.y <= 290)
		{
			utils::DrawRect({515,220,250,70}, 5.0f);//first
		}
	}
}

void MenuMain::MouseMoved(const Point2f& mousePos)
{
	m_MousePos = mousePos;
}

void MenuMain::MouseClick(const SDL_MouseButtonEvent& e) const
{
	if (m_MousePos.x >= 515 && m_MousePos.x <= 765)
	{
		if (m_MousePos.y >= 420 && m_MousePos.y <= 490)
		{
			m_Manager.SetState(MenuManager::MenuState::menuStory);
			SoundManager::PlaySoundStream("Story", true);
		}
		else if (m_MousePos.y >= 320 && m_MousePos.y <= 390)
		{
			m_Manager.SetState(MenuManager::MenuState::menuExtra);
		}
		else if (m_MousePos.y >= 220 && m_MousePos.y <= 290)
		{
			m_Manager.SetState(MenuManager::MenuState::menuQuit);
		}
	}
}
