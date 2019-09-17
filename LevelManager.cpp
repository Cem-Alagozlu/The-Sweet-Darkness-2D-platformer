#include "stdafx.h"
#include "LevelManager.h"
#include "LevelBase.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "LevelThree.h"
#include "LevelFour.h"
#include "LevelEnd.h"
#include "LevelBoss.h"
#include "SoundManager.h"

std::shared_ptr<LevelBase> LevelManager::m_pCurrentLevel{};

LevelManager::LevelManager(Game& game, std::shared_ptr<Player> player)
	: m_Game{game}
	  , m_pLevelOne{std::make_shared<LevelOne>(*this, player)}
	  , m_pLevelTwo{std::make_shared<LevelTwo>(*this, player)}
	  , m_pLevelThree{std::make_shared<LevelThree>(*this, player)}
	  , m_pLevelFour{std::make_shared<LevelFour>(*this, player)}
	  , m_pLevelBoss{std::make_shared<LevelBoss>(*this, player)}
	  , m_pLevelEnd{std::make_shared<LevelEnd>(*this, player, game)}
	  , m_pPlayer{player}

{
	SetCurrentLevel(Level::noLevel);
}


void LevelManager::DrawForeground() const
{
	m_pCurrentLevel->DrawFront();
}

void LevelManager::DrawBackground() const
{
	m_pCurrentLevel->DrawBack();
}

void LevelManager::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const
{
	m_pCurrentLevel->HandleCollision(actorShape, actorVelocity);
}

void LevelManager::Update(float elapsedSec) const
{
	m_pCurrentLevel->Update(elapsedSec);
}

void LevelManager::MouseMoved(const Point2f& mousePos) const
{
	m_pCurrentLevel->MouseMoved(mousePos);
}

void LevelManager::MouseClick(const SDL_MouseButtonEvent& e) const
{
	m_pCurrentLevel->MouseClick(e);
}

std::shared_ptr<LevelBase> LevelManager::GetCurrentLevel()
{
	return m_pCurrentLevel;
}

void LevelManager::SetCurrentLevel(Level level)
{
	m_CurrentLevel = level;

	switch (m_CurrentLevel)
	{
	case Level::levelOne:
		m_pCurrentLevel = m_pLevelOne;
		SoundManager::PlaySoundEffect("Wind", true, false);
		SoundManager::PlaySoundStream("LevelOne", true);
		break;
	case Level::levelTwo:
		m_pCurrentLevel = m_pLevelTwo;
		SoundManager::PlaySoundEffect("Wind", true, false);
		SoundManager::PlaySoundStream("LevelTwo", true);
		break;
	case Level::levelThree:
		m_pCurrentLevel = m_pLevelThree;
		SoundManager::PlaySoundEffect("Wind", true, false);
		SoundManager::PlaySoundStream("LevelThree", true);
		break;
	case Level::levelFour:
		m_pCurrentLevel = m_pLevelFour;
		SoundManager::PlaySoundEffect("Wind", true, false);
		SoundManager::PlaySoundStream("LevelFour", true);
		break;
	case Level::LevelEnd:
		m_pCurrentLevel = m_pLevelEnd;
		SoundManager::PlaySoundStream("End", true);
		break;
	case Level::levelBoss:
		m_pCurrentLevel = m_pLevelBoss;
		SoundManager::PlaySoundStream("Boss", false);
		break;
	default:
		break;
	}

	if (m_pCurrentLevel != nullptr)
	{
		m_pPlayer.lock()->SetLevelBeginPos(m_pCurrentLevel->GetBeginPos());
		m_pPlayer.lock()->SetPosition(m_pCurrentLevel->GetBeginPos());
	}
}

Point2f LevelManager::GetLevelBeginPos() const
{
	return m_pCurrentLevel->GetBeginPos();
}
