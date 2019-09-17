#include "stdafx.h"
#include "MenuQuit.h"
#include "utils.h"
#include "MenuManager.h"


MenuQuit::MenuQuit(MenuManager& manager)
	: m_Manager{manager}
{
	m_pMenuQuitText.push_back(std::make_unique<Texture>("Are you sure", "Resources/Fonts/Font00.ttf", 60, Color4f{1,1,1,1}));
	m_pMenuQuitText.push_back(std::make_unique<Texture>("that you want", "Resources/Fonts/Font00.ttf", 60, Color4f{1,1,1,1}));
	m_pMenuQuitText.push_back(std::make_unique<Texture>("to quit ?", "Resources/Fonts/Font00.ttf", 60, Color4f{1,1,1,1}));
	m_pMenuQuitText.push_back(std::make_unique<Texture>("Yes", "Resources/Fonts/Font00.ttf", 60, Color4f{1,1,1,1}));
	m_pMenuQuitText.push_back(std::make_unique<Texture>("No", "Resources/Fonts/Font00.ttf", 60, Color4f{1,1,1,1}));
}


void MenuQuit::Draw() const
{
	utils::FillRect({400,300,440,300});// big
	utils::FillRect({400,200,200,70}); // yes
	utils::FillRect({640,200,200,70}); // no

	m_pMenuQuitText[0]->Draw({430,520});// are you sure
	m_pMenuQuitText[1]->Draw({410,440});// that you want
	m_pMenuQuitText[2]->Draw({510,330});// to quit?
	m_pMenuQuitText[3]->Draw({445,200});// yes
	m_pMenuQuitText[4]->Draw({700,200});// no

	// borders
	if (m_MousePos.y >= 200 && m_MousePos.y <= 270)
	{
		if (m_MousePos.x >= 400 && m_MousePos.x <= 600)//yes
		{
			utils::DrawRect({400,200,200,70}, 4.0f);
		}
		else if (m_MousePos.x >= 640 && m_MousePos.x <= 840)
		{
			utils::DrawRect({640,200,200,70}, 4.0f);//no
		}
	}
}

void MenuQuit::MouseMoved(const Point2f& mousePos)
{
	m_MousePos = mousePos;
}

void MenuQuit::MouseClick(const SDL_MouseButtonEvent& e) const
{
	if (m_MousePos.y >= 200 && m_MousePos.y <= 270)
	{
		if (m_MousePos.x >= 400 && m_MousePos.x <= 600)//yes
		{
			SDL_Event quit;
			quit.type = SDL_QUIT;
			SDL_PushEvent(&quit);
		}
		else if (m_MousePos.x >= 640 && m_MousePos.x <= 840)
		{
			MenuManager::SetState(MenuManager::MenuState::menuMain);
		}
	}
}
