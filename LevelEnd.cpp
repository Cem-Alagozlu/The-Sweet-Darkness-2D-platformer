#include "stdafx.h"
#include "LevelEnd.h"
#include "Game.h"
#include "SoundManager.h"

LevelEnd::LevelEnd(LevelManager& levelmanager, std::shared_ptr<Player> player, Game& game)
	: LevelBase{levelmanager,"Resources/Images/Sprites/Levels/end/end-level.svg"}
	  , m_Game{game}
	  , m_FogFront{"Resources/Images/Sprites/Levels/End/Fog.png"}
	  , m_End{"Resources/Images/Sprites/Levels/End/1.png"}
	  , m_pPlayer{player}, m_PosX(0), m_PosY(0)
{
	m_pLevelEndTexture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/End/end.png");

	m_Boundaries = {0,0,m_pLevelEndTexture->GetWidth(),m_pLevelEndTexture->GetHeight()};

	m_BeginPos = Point2f{8450,30};

	m_CamChangeX = -2800;
	m_CamChangeY = 0;
}

void LevelEnd::DrawFront() const
{
	m_pLevelEndTexture->Draw(Rectf{0,0,9000,1000});
	m_pPlayer.lock()->Draw();
	m_FogFront.Draw(Rectf{5000,0,4000,1000});

	if (m_PhaseTwo)
	{
		m_End.Draw(Rectf{7720,0,1280,720});
	}

	utils::SetColor({1,1,1,m_Alpha});
	utils::FillRect(m_FadeBox);

	if (m_pPlayer.lock()->m_IsCommitedSuicide())
	{
		utils::SetColor({0,0,0,m_Alpha});
		utils::FillRect(m_FadeBoxOut);
	}
}


void LevelEnd::Update(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	Game::m_CamY = m_CamChangeY;
	Game::m_CamX = m_CamChangeX;
	float camPosAdder{1};

	m_pPlayer.lock()->SetMovement(true);


	if (m_PhaseOne)
	{
		if (m_CamChangeX >= -2750 && m_CamChangeX <= 0)
		{
			camPosAdder = camPosAdder + elapsedSec + 2;
		}

		m_CamChangeX += camPosAdder;

		if (m_Alpha >= 0)
		{
			m_Alpha -= 0.00095f;
		}

		if (m_CamChangeX >= 15)
		{
			m_PhaseTwo = true;
			m_PhaseOne = false;
		}
	}

	if (m_PhaseTwo)
	{
		m_pPlayer.lock()->SetEnding(true);
	}
	if (m_pPlayer.lock()->m_IsCommitedSuicide())
	{
		if (m_Alpha >= 0.95f)
		{
			SoundManager::PlaySoundEffect("Death", false, true);
		}
	}

	if (pStates[SDL_SCANCODE_UP])
	{
		m_IsButtonPressed = true;
	}
	if (m_IsButtonPressed)
	{
		m_Alpha += 0.0095f;
		if (m_Alpha >= 1)
		{
			m_LevelManager.SetCurrentLevel(LevelManager::Level::levelOne);
			SoundManager::PlaySoundStream("Credits", true);
			m_Game.SetState(Game::WindowState::credits);
		}
	}
	std::cout << m_Alpha << std::endl;
}

void LevelEnd::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	LevelBase::HandleCollision(actorShape, actorVelocity);
}

Rectf LevelEnd::GetBoundaries() const
{
	return Rectf{};
}

void LevelEnd::DrawBack() const
{
}

void LevelEnd::MouseMoved(const Point2f& mousePos)
{
}

void LevelEnd::MouseClick(const SDL_MouseButtonEvent& e)
{
}

bool LevelEnd::HasReachedEnd(const Rectf& actorShape) const
{
	return false;
}

void LevelEnd::DeathCollision()
{
}
