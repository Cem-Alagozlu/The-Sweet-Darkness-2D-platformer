#include "stdafx.h"
#include "MenuManager.h"
#include <sstream>
#include "MenuMain.h"
#include "MenuQuit.h"
#include "MenuExtra.h"
#include "MenuStory.h"
#include "LevelManager.h"

MenuManager::MenuState MenuManager::m_MenuState{MenuState::menuMain};

MenuManager::MenuManager(Game& game, LevelManager& levelManager)
	: m_Game{game}
	  , m_pMenuExtra{std::make_shared<MenuExtra>(*this)}
	  , m_pMenuQuit{std::make_shared<MenuQuit>(*this)}
	  , m_pMenuMain{std::make_shared<MenuMain>(*this)}
	  , m_pMenuStory{std::make_shared<MenuStory>(*this, game, levelManager)}
{
	InitializeBackground();
}

void MenuManager::Draw() const
{
	m_pMenuImgs[m_MenuIMGS01 % 300]->Draw(Rectf{0,0,1280.0f,720.0f});

	switch (m_MenuState)
	{
	case MenuState::menuMain:
		m_pMenuMain->Draw();
		break;
	case MenuState::menuExtra:
		m_pMenuExtra->DrawExtraMain();
		break;
	case MenuState::menuQuit:
		m_pMenuQuit->Draw();
		break;
	case MenuState::menuStory:
		m_pMenuStory->Draw();
		break;
	case MenuState::menuExtraStory:
		m_pMenuExtra->DrawExtraStory();

		break;
	case MenuState::menuExtraOptions:
		m_pMenuExtra->DrawExtraOptions();
		break;
	case MenuState::menuExtraCredits:
		m_pMenuExtra->DrawExtraCredits();
		break;
	}
}

void MenuManager::Update(float elapsedSec)
{
	UpdateBackground(elapsedSec);

	switch (m_MenuState)
	{
	case MenuState::menuMain:
		break;
	case MenuState::menuExtra:
		m_pMenuExtra->Update(elapsedSec);
		break;
	case MenuState::menuQuit:
		break;
	case MenuState::menuStory:
		break;
	case MenuState::menuExtraStory:
		break;
	case MenuState::menuExtraOptions:
		m_pMenuExtra->Update(elapsedSec);
		break;
	default: ;
	}
}

void MenuManager::MouseMoved(const Point2f& mousePos) const
{
	switch (m_MenuState)
	{
	case MenuState::menuMain:
		m_pMenuMain->MouseMoved(mousePos);
		break;
	case MenuState::menuExtra:
		m_pMenuExtra->MouseMoved(mousePos);
		break;
	case MenuState::menuQuit:
		m_pMenuQuit->MouseMoved(mousePos);
		break;
	case MenuState::menuStory:
		m_pMenuStory->MouseMoved(mousePos);
		break;
	case MenuState::menuExtraStory:
		m_pMenuExtra->MouseMoved(mousePos);
		break;
	case MenuState::menuExtraOptions:
		m_pMenuExtra->MouseMoved(mousePos);
		break;
	case MenuState::menuExtraCredits:
		m_pMenuExtra->MouseMoved(mousePos);
		break;
	}
}

void MenuManager::MouseClick(const SDL_MouseButtonEvent& e) const
{
	switch (m_MenuState)
	{
	case MenuState::menuMain:
		m_pMenuMain->MouseClick(e);
		break;
	case MenuState::menuExtra:
		m_pMenuExtra->MouseClick(e);
		break;
	case MenuState::menuQuit:
		m_pMenuQuit->MouseClick(e);
		break;
	case MenuState::menuStory:
		m_pMenuStory->MouseClick(e);
		break;
	case MenuState::menuExtraStory:
		m_pMenuExtra->MouseClickBack(e);
		break;
	case MenuState::menuExtraOptions:
		m_pMenuExtra->MouseClickBack(e);
		m_pMenuExtra->MouseClick(e);
		break;
	case MenuState::menuExtraCredits:
		m_pMenuExtra->MouseClickBack(e);
		break;
	}
}

void MenuManager::SetState(MenuState state)
{
	m_MenuState = state;
}

void MenuManager::InitializeBackground()
{
	for (int idx = 0; idx < m_MenuAmount; ++idx)
	{
		std::stringstream str;
		str << "Resources/Images/Menu/Background/img (" << idx + 1 << ")" << ".jpg";
		m_pMenuImgs.push_back(std::make_unique<Texture>(str.str()));
	}
}

void MenuManager::UpdateBackground(float elapsedSec)
{
	m_ElapsedTime += elapsedSec;
	do
	{
		m_MenuIMGS01++;
	}
	while (m_MenuIMGS01 == 300);
}

void MenuManager::FullScreenOn() const
{
	m_Game.FullScreenOn();
}

void MenuManager::FullScreenOff() const
{
	m_Game.FullScreenOff();
}

void MenuManager::VsyncOn() const
{
	m_Game.VsyncOn();
}

void MenuManager::VsyncOff() const
{
	m_Game.VsyncOff();
}
