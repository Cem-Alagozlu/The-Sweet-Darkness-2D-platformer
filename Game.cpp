#include "stdafx.h"
#include "Game.h"
#include "Core.h"

float Game::m_CamX = 0;
float Game::m_CamY = 0;

Game::Game(const Window& window, Core& core)
	: m_Window{window}
	  , m_MenuIntro{*this,true}
	  , m_Core{core}
	  , m_pPlayer{std::make_shared<Player>()}
	  , m_pLevelManager{std::make_shared<LevelManager>(*this, m_pPlayer)}
	  , m_pMenuManager{std::make_shared<MenuManager>(*this, *m_pLevelManager.get())}
	  , m_Credits(*this)
	  , m_Hud{m_pPlayer->GetLives(),m_pPlayer->GetCoins()}
{
	
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
	m_Camera.SetSize(Vector2f(m_Window.width, m_Window.height));
	m_Camera.SetBoundaries(Rectf{0,0,9000,2400});
}

void Game::Cleanup() const
{
}

void Game::Update(float elapsedSec)
{
	UpdateWindowStates(elapsedSec);
	m_Camera.Update({m_pPlayer->GetShape().left + m_CamX,m_pPlayer->GetShape().bottom + m_CamY,m_pPlayer->GetShape().width,m_pPlayer->GetShape().height});
	m_Hud.Update(elapsedSec);
}

void Game::Draw() const
{
	ClearBackground();
	DrawWindowStates();
}

void Game::DrawLevels() const
{
	glPushMatrix();
	glTranslatef(-m_Camera.GetPosition().x, -m_Camera.GetPosition().y, 0);
	m_pLevelManager->DrawBackground();
	m_pPlayer->Draw();
	m_pLevelManager->DrawForeground();
	glPopMatrix();
	m_Hud.Draw();
}

void Game::FullScreenOn() const
{
	m_Core.SetFullScreenOn();
}

void Game::FullScreenOff() const
{
	m_Core.SetFullScreenOff();
}

void Game::VsyncOn() const
{
	m_Core.ToggleVsyncOn();
}

void Game::VsyncOff() const
{
	m_Core.ToggleVsyncOff();
}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e) const
{
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	if (e.keysym.sym == SDLK_f)
	{
		m_Core.SetFullScreen();
	}
	if (e.keysym.sym == SDLK_ESCAPE)
	{
		m_WindowState = WindowState::menu;
		m_pMenuManager->SetState(MenuManager::MenuState::menuQuit);
	}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	m_MousePosition.x = float(e.x);
	m_MousePosition.y = m_Window.height - e.y;

	switch (m_WindowState)
	{
	case WindowState::menu:
		m_pMenuManager->MouseMoved(m_MousePosition);
		break;
	case WindowState::game:
		m_pLevelManager->MouseMoved(m_MousePosition);
		break;
	default: ;
	}
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e) const
{
	switch (m_WindowState)
	{
	case WindowState::menu:
		m_pMenuManager->MouseClick(e);
		break;
	case WindowState::game:
		m_pLevelManager->MouseClick(e);
		break;
	case WindowState::credits:
		m_Credits.MouseClick(e);
	default:
		break;
	}
}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e) const
{
}

void Game::ClearBackground() const
{
	glClearColor(1, 1, 1, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::DrawWindowStates() const
{
	switch (m_WindowState)
	{
	case WindowState::intro:
		m_MenuIntro.Draw();
		break;
	case WindowState::menu:
		m_pMenuManager->Draw();
		break;
	case WindowState::game:
		DrawLevels();
		break;
	case WindowState::credits:
		m_Credits.DrawFront();
		break;
	default:
		break;
	}
}

void Game::UpdateWindowStates(float elapsedSec)
{
	switch (m_WindowState)
	{
	case WindowState::intro:
		m_MenuIntro.Update(elapsedSec);
		break;
	case WindowState::menu:
		m_pMenuManager->Update(elapsedSec);
		break;
	case WindowState::game:
		m_pLevelManager->Update(elapsedSec);
		m_pPlayer->Update(elapsedSec, m_pLevelManager->GetCurrentLevel());
		break;
	case WindowState::credits:
		m_Credits.Update(elapsedSec);
	}
}

void Game::SetState(WindowState state)
{
	m_WindowState = state;
}
