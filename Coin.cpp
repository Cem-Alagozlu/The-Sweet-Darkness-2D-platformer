#include "stdafx.h"
#include "Coin.h"
#include "SoundManager.h"


Coin::Coin(const Point2f& pos)
{
	m_pCoinSprite = std::make_shared<Sprite>("Resources/Images/Sprites/Extra/Coins.png", 0.0f, 0.0f, 1500.0f, 142.0f, 10, 1, 10);

	m_Shape.center.x = pos.x + m_pCoinSprite->GetWidth() / 2;
	m_Shape.center.y = pos.y + m_pCoinSprite->GetHeight() / 2;
	m_Shape.radius = 15;
}


Coin::~Coin()
{
}

void Coin::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Shape.center.x, m_Shape.center.y, 0);
	glScalef(m_Scale, m_Scale, 1.0f);
	glTranslatef(-m_pCoinSprite->GetWidth() / 2, -m_pCoinSprite->GetHeight() / 2, 0);
	m_pCoinSprite->Draw();
	glPopMatrix();
}

void Coin::Update(float elapsedSec) const
{
	m_pCoinSprite->Update(elapsedSec);
}

bool Coin::IsOverlapping(const Rectf& rect) const
{
	if (utils::IsOverlapping(rect, m_Shape))
	{
		return true;
	}
	return false;
}

void Coin::PlayCoinSound() const
{
	SoundManager::PlaySoundEffect("Coin", false, false);
}
