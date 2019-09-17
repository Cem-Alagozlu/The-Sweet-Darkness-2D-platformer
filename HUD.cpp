#include "stdafx.h"
#include "HUD.h"


HUD::HUD(const int& life, const int& coins)
	: m_LifeCounter{life}
	  , m_PreviousLCounter(0), m_CoinCounter{coins}
	  , m_NameTexture01{"Daevas","Resources/Fonts/Font01.ttf",35,{1,1,1,1}}
	  , m_NameTexture02{": x","Resources/Fonts/Font02.ttf",25,{1,1,1,1}}
	  , m_CoinTexture{"Resources/Images/Sprites/Extra/gold01.png"}
{
}

HUD::~HUD()
{
}

void HUD::Update(float elapsedSec)
{
	if (m_PreviousLCounter != m_LifeCounter)
	{
		m_LifeCounterTexture = std::make_unique<Texture>(std::to_string(m_LifeCounter), "Resources/Fonts/Font02.ttf", 30, Color4f(1, 1, 1, 1));
	}

	if (m_PreviousCCounter != m_CoinCounter)
	{
		m_CoinCounterTexture = std::make_unique<Texture>(std::to_string(m_CoinCounter), "Resources/Fonts/Font02.ttf", 30, Color4f(1, 1, 1, 1));
	}
}

void HUD::Draw() const
{
	//Draw upper bar 
	utils::SetColor({0,0,0,0.75f});
	utils::FillRect({0,680,1280,40});

	//Draw player name + Life counter
	m_NameTexture01.Draw({5,680});
	m_NameTexture02.Draw({110,688});
	m_LifeCounterTexture->Draw({160,688});

	//Draw Coin + counter
	glPushMatrix();
	glTranslatef(1150, 686, 0);
	glScalef(0.05f, 0.05f, 1.0f);
	m_CoinTexture.Draw({0,0});
	glPopMatrix();

	m_NameTexture02.Draw({1180,686});
	m_CoinCounterTexture->Draw({1222,686});
}
