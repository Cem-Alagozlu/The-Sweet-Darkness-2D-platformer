#include "stdafx.h"
#include  "MenuIntro.h"
#include "Game.h"

MenuIntro::MenuIntro(Game& game, bool playIntro)
	: m_Game{game}
{
	m_Afbeeldingen.push_back(std::make_shared<Texture>("Resources/Images/Intro/1.png"));
	m_Afbeeldingen.push_back(std::make_shared<Texture>("Resources/Images/Intro/2.png"));
	m_Afbeeldingen.push_back(std::make_shared<Texture>("Resources/Images/Intro/3.png"));
}


void MenuIntro::Update(float elapsedSec)
{
	SoundManager::PlaySoundStream("Intro", true);
	if (m_IsFadeIN == false)
	{
		m_Alpha -= 0.0095f;
	}
	else
	{
		m_Alpha += 0.0095f;
	}

	if (m_Alpha >= 1.0f)
	{
		m_IsFadeIN = false;
		++m_IndexAfbeeldingen;
	}
	else if (m_Alpha <= 0.0f)
	{
		m_IsFadeIN = true;
	}

	if (m_IndexAfbeeldingen > 2)
	{
		m_Game.SetState(Game::WindowState::menu);
	}
}

void MenuIntro::Draw() const
{
	utils::SetColor({0,0,0,m_Alpha});
	m_Afbeeldingen[m_IndexAfbeeldingen]->Draw({0,0,1280,720});


	utils::FillRect(m_FadeBox);
}
