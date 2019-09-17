#include "stdafx.h"
#include "LevelBoss.h"
#include <sstream>
#include "SoundManager.h"

LevelBoss::LevelBoss(LevelManager& levelmanager, std::shared_ptr<Player> player)
	: LevelBase{levelmanager,"Resources/Images/Sprites/Levels/Boss/boss01.svg"}
	  , m_LowerBodyBoss{"Resources/Images/Sprites/Levels/Boss/boss01.png"}
	  , m_UpperBodyBoss{"Resources/Images/Sprites/Levels/Boss/boss02.png"}
	  , m_FrontFog{"Resources/Images/Sprites/Levels/Boss/1.png"}
	  , m_Sky{"Resources/Images/Sprites/Levels/Boss/2.png"}
	  , m_pPlayer{player}
	  , m_SwingBounderies{25}
	  , m_Angle{0}
{
	m_PosX = 0;
	m_PosY = 0;

	m_Boundaries = {0,0,1280,720};

	for (int idx = 0; idx < m_imgAmount; ++idx)
	{
		std::stringstream str;
		str << "Resources/Images/Sprites/Levels/Boss/Instructions/" << idx + 1 << ".png";
		m_pExplaining.push_back(std::make_unique<Texture>(str.str()));
	}
}

void LevelBoss::DrawFront() const
{
	m_LowerBodyBoss.Draw(Rectf{0,0,1280,720});
	DrawHead();
	m_pPlayer.lock()->Draw();
	m_FrontFog.Draw(Rectf{0,0,2000,1000});


	utils::SetColor({0,0,0,m_Alpha});
	utils::FillRect(m_FadeBox);

	if (m_IntroTimer >= 0 && m_IntroTimer <= 50.0f)
	{
		m_pExplaining[m_imgNumber]->Draw({0,0});
	}
	if (m_PhaseOne && m_pPlayer.lock()->GetPosition().x >= 551)
	{
		utils::SetColor({200.0f / 255.0f,0,0,1});
		utils::FillEllipse(460, 610, 15, 15);
		utils::FillEllipse(755, 595, 15, 15);

		utils::DrawLine({460,610}, {m_pPlayer.lock()->GetPosition().x + +35,m_pPlayer.lock()->GetPosition().y + 35}, 10);
		utils::DrawLine({755,595}, {m_pPlayer.lock()->GetPosition().x + 35,m_pPlayer.lock()->GetPosition().y + 35}, 10);
	}
}

void LevelBoss::DrawBack() const
{
	m_Sky.Draw(Rectf{0,0,2000,1000});
}

void LevelBoss::Update(float elapsedSec)
{
	m_PosX = m_pPlayer.lock()->GetShape().left;
	m_PosY = m_pPlayer.lock()->GetShape().bottom;

	m_pPlayer.lock()->SetMovement(true);


	if (m_IsPositive)
	{
		m_Angle = m_Angle + 0.2f;
	}
	else if (m_IsPositive == false)
	{
		m_Angle = m_Angle - 0.2f;
	}
	if (m_Angle <= -m_SwingBounderies)
	{
		m_IsPositive = true;
	}
	if (m_Angle >= m_SwingBounderies)
	{
		m_IsPositive = false;
	}

	m_IntroTimer = m_IntroTimer + elapsedSec;
	IntroText();

	if (m_PhaseOne == true && m_pPlayer.lock()->GetPosition().x >= 551)
	{
		m_IsLaserOn = true;
	}
}


void LevelBoss::DrawHead() const
{
	glPushMatrix();
	glTranslatef(575, 120, 0);
	glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
	glScalef(1, 1, 1.0f);
	glTranslatef(-m_UpperBodyBoss.GetWidth() / 2, 0, 0.0f);
	m_UpperBodyBoss.Draw({0.0f,0.0f});
	glPopMatrix();
}

void LevelBoss::MouseMoved(const Point2f& mousePos)
{
}

void LevelBoss::MouseClick(const SDL_MouseButtonEvent& e)
{
}

Rectf LevelBoss::GetBoundaries() const
{
	return Rectf{};
}

bool LevelBoss::HasReachedEnd(const Rectf& actorShape) const
{
	return false;
}

void LevelBoss::DeathCollision()
{
}

void LevelBoss::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	LevelBase::HandleCollision(actorShape, actorVelocity);

	if (actorShape.left >= 20 && actorShape.left <= 971)
	{
		SoundManager::PlaySoundEffect("Wind2", false, true);
	}

	if (actorShape.left >= 0 && actorShape.left <= 580 && m_IntroTimer >= 50.0f)
	{
		actorShape.left += 3.0f;
	}
	if (actorShape.left >= 550)
	{
		m_Angle = 0.0f;
		m_PhaseOne = true;
	}
	if (m_IsLaserOn)
	{
		if (actorShape.left >= 540 && actorShape.left <= 971)
		{
			actorShape.left += 3.0f;
			SoundManager::PlaySoundEffect("Laser", true, true);
		}
		if (actorShape.left >= 970)
		{
			m_pPlayer.lock()->SetSecondaryMovement(Character::SecondaryMovement::death);
			m_LevelManager.SetCurrentLevel(LevelManager::Level::LevelEnd);
			SoundManager::StopSoundEffect("Laser");
		}
	}
}


void LevelBoss::IntroText()
{
	if (m_IntroTimer >= 0 && m_IntroTimer <= 3.5f)
	{
		m_imgNumber = 0;
	}

	if (m_IntroTimer >= 3.6f && m_IntroTimer <= 6.1f)
	{
		m_imgNumber = 1;
	}

	if (m_IntroTimer >= 6.2f && m_IntroTimer <= 9.5f)
	{
		m_imgNumber = 2;
	}

	if (m_IntroTimer >= 9.6f && m_IntroTimer <= 12.0f)
	{
		m_imgNumber = 3;
	}

	if (m_IntroTimer >= 13.1f && m_IntroTimer <= 14.9f)
	{
		m_imgNumber = 4;
	}
	if (m_IntroTimer >= 15.0f && m_IntroTimer <= 18.0f)
	{
		m_imgNumber = 5;
	}
	if (m_IntroTimer >= 18.1f && m_IntroTimer <= 20.7f)
	{
		m_imgNumber = 6;
	}
	if (m_IntroTimer >= 20.8f && m_IntroTimer <= 23.0f)
	{
		m_imgNumber = 7;
	}

	if (m_IntroTimer >= 23.1f && m_IntroTimer <= 25.5f)
	{
		m_imgNumber = 8;
	}

	if (m_IntroTimer >= 25.6f && m_IntroTimer <= 28.0f)
	{
		m_imgNumber = 9;
	}

	if (m_IntroTimer >= 28.1f && m_IntroTimer <= 30.8f)
	{
		m_imgNumber = 10;
		m_Alpha -= 0.0095f;
	}

	if (m_IntroTimer >= 30.9f && m_IntroTimer <= 33.9f)
	{
		m_imgNumber = 11;
		m_Alpha = 0;
	}
	if (m_IntroTimer >= 40.0f && m_IntroTimer <= 43.0f)
	{
		m_imgNumber = 12;
	}
	if (m_IntroTimer >= 43.1f && m_IntroTimer <= 47.0f)
	{
		m_imgNumber = 13;
	}
	if (m_IntroTimer >= 50)
	{
		m_IntroTimer = 55.0f;
		m_PhaseOne = true;
	}
}
