#include "stdafx.h"
#include "Credits.h"
#include <sstream>
#include "Game.h"

Credits::Credits(Game& game)
	: m_Game{game}
{
	for (int idx = 0; idx < m_imgAmount; ++idx)
	{
		std::stringstream str;
		str << "Resources/Images/Sprites/Levels/Credits/" << idx + 1 << ".png";
		m_Credits.push_back(std::make_unique<Texture>(str.str()));
	}
}


void Credits::DrawFront() const
{
	utils::SetColor({0,0,0,m_Alpha});
	m_Credits[m_IndexAfbeeldingen]->Draw({0,0,1280,720});

	if (m_IndexAfbeeldingen < 7)
	{
		utils::FillRect(m_FadeBox);
	}
}

void Credits::Update(float elapsedSec)
{
	if (m_IndexAfbeeldingen < 7)
	{
		if (m_IsFadeIN == false)
		{
			m_Alpha -= 0.009f;
		}
		else
		{
			m_Alpha += 0.009f;
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
	}


	if (m_IndexAfbeeldingen == m_imgAmount)
	{
		m_IndexAfbeeldingen = 7;
	}
}

void Credits::MouseClick(const SDL_MouseButtonEvent& e) const
{
	if (m_IndexAfbeeldingen == 7)
	{
		SDL_Event quit;
		quit.type = SDL_QUIT;
		SDL_PushEvent(&quit);
	}
}
