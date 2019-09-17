#include "stdafx.h"
#include "Player.h"
#include "LevelBase.h"
#include "SoundManager.h"

Player::Player()
	: Character{Rectf{0,0,0,0}}
	  , m_IsMoving(false), m_Jump{"Resources/Images/Sprites/Player/Shadow_Boy/jump.png", 0.0f, 0.0f, 7271.0f, 1794.0f, 5, 1, 10}
	  , m_Idle{"Resources/Images/Sprites/Player/Shadow_Boy/idle.png", 0.0f, 0.0f, 5882.0f, 1794.0f, 4, 1, 10}
	  , m_Walk{"Resources/Images/Sprites/Player/Shadow_Boy/walk.png", 0.0f, 0.0f, 5882.0f, 1794.0f, 4, 1, 10}
	  , m_Death{"Resources/Images/Sprites/Player/Shadow_Boy/death.png", 0.0f, 0.0f, 8000.0f, 1794.0f, 8, 1, 10}
	  , m_Climbing{"Resources/Images/Sprites/Player/Shadow_Boy/climbing.png", 0.0f, 0.0f, 7271, 3588,5,2,12}
	  , m_Suicide{"Resources/Images/Sprites/Player/Shadow_Boy/Suicide.png", 0.0f, 0.0f, 600, 300,3,1,10}
	  , m_pCurrentSprite(nullptr)
	  , m_Width(0)
	  , m_Height(0)
{
	m_Scale = 0.1f;


	m_CollisonBox.width = m_Idle.GetWidth() * 0.60f * m_Scale;
	m_CollisonBox.height = m_Idle.GetHeight() * 0.75f * m_Scale;
}

Player::~Player()
{
	m_pCurrentSprite = nullptr;
}

void Player::Update(float elapsedSec, std::shared_ptr<LevelBase> level)
{
	UpdateSprite(elapsedSec);
	UpdateCollision(level);
	if (m_Velocity.x == 0 && m_Velocity.y == 0 && m_Smovement != SecondaryMovement::death)
	{
		m_Smovement = SecondaryMovement::idle;
	}
	if (m_Velocity.y == 0)
	{
		m_IsJumping = false;
	}
	UpdatePosition(elapsedSec);
	HandleMoveKeysState(elapsedSec);
	UpdateReset(elapsedSec);

	if (m_Coins == 20)
	{
		m_Lives = m_Lives + 1;
		m_Coins = 0;

		SoundManager::PlaySoundEffect("LifeUp", false, false);
	}

	if (m_Lives <= 0)
	{
	}
}

void Player::UpdateSprite(float elapsedSec)
{
	switch (m_Smovement)
	{
	case SecondaryMovement::idle:
		StopSoundEffects("Idle");
		m_pCurrentSprite = &m_Idle;
		break;
	case SecondaryMovement::walk:
		StopSoundEffects("Grass");
		m_pCurrentSprite = &m_Walk;
		SoundManager::PlaySoundEffect("Grass", false, true);
		break;
	case SecondaryMovement::jump:
		StopSoundEffects("Jump");
		m_pCurrentSprite = &m_Jump;
		break;
	case SecondaryMovement::death:
		m_pCurrentSprite = &m_Death; //adress krijgen
		break;
	case SecondaryMovement::climbing:
		m_pCurrentSprite = &m_Climbing;
	default:
		break;
	}

	m_pCurrentSprite->Update(elapsedSec);
}

void Player::UpdatePosition(float elapsedSec)
{
	m_CollisonBox.left += m_Velocity.x * elapsedSec;
	m_CollisonBox.bottom += m_Velocity.y * elapsedSec;
}

void Player::UpdateCollision(std::shared_ptr<LevelBase> level)
{
	level->HandleCollision(m_CollisonBox, m_Velocity);
}

void Player::UpdateReset(float elapsedSec)
{
	if (m_Smovement == SecondaryMovement::death)
	{
		if (!m_HasPlayedDeathSound)
		{
			SoundManager::PlaySoundEffect("Death", false, true);
			m_HasPlayedDeathSound = true;
		}

		if (m_pCurrentSprite->HasEnded())
		{
			SetMovement(false);
			m_pCurrentSprite->Lock();
			m_Velocity.y -= 50.0f;
			m_TotalAccum += elapsedSec;
			if (m_TotalAccum >= m_TotalTimerReset)
			{
				SetPosition(m_BeginPosition);
				m_pCurrentSprite->Unlock();
				SetMovement(true);
				m_Smovement = SecondaryMovement::idle;
				m_TotalAccum = 0.0f;
				m_Lives = m_Lives - 1;
				m_HasPlayedDeathSound = false;
				m_Walk.Unlock();
				m_Jump.Unlock();
				m_Climbing.Unlock();
				m_Death.Unlock();
				m_Idle.Unlock();
			}
		}
	}
}

void Player::Draw() const
{
	Vector2f offset{m_CollisonBox.width - m_pCurrentSprite->GetWidth() * m_Scale, m_CollisonBox.height - m_pCurrentSprite->GetHeight() * m_Scale};

	glPushMatrix();
	glTranslatef(m_CollisonBox.left + offset.x / 2, m_CollisonBox.bottom, 0);
	glScalef(m_Scale, m_Scale, 1);
	if (m_Pmovement == PrimaryMovement::left)
	{
		m_pCurrentSprite->Draw(true);
	}
	else if (m_Pmovement == PrimaryMovement::right)
	{
		m_pCurrentSprite->Draw(false);
	}
	glPopMatrix();
	//DrawDebugHelp();
}

void Player::DrawDebugHelp() const
{
	Point2f actorBottomPos{GetShape().left + GetShape().width / 2, GetShape().bottom};
	Point2f actorTopPos{GetShape().left + GetShape().width / 2, GetShape().bottom + GetShape().height};

	Point2f actorLeftPos{GetShape().left , GetShape().bottom + GetShape().height / 2};
	Point2f actorRightPos{GetShape().left + GetShape().width , GetShape().bottom + GetShape().height / 2};

	utils::DrawLine(actorBottomPos, actorTopPos);
	utils::DrawLine(actorLeftPos, actorRightPos);
	utils::DrawRect(GetShape());

	//std::cout << int(m_Pmovement) << " primary " << int(m_Smovement) << " secondary" << std::endl;
	std::cout << GetShape().left << " x " << GetShape().bottom << " y" << GetShape().width << " " << GetShape().height << " " << std::endl;
}

void Player::HandleMoveKeysState(float elapsedSec)
{
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);

	m_Velocity.x = 0.0f;


	if (m_IsMoving == true && m_Smovement != SecondaryMovement::death)
	{
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			m_Velocity.x += m_HorSpeed;
			m_Pmovement = PrimaryMovement::right;
			m_Smovement = SecondaryMovement::walk;
		}
		if (pStates[SDL_SCANCODE_LEFT])
		{
			m_Velocity.x -= m_HorSpeed;
			m_Pmovement = PrimaryMovement::left;
			m_Smovement = SecondaryMovement::walk;
		}
		if (pStates[SDL_SCANCODE_SPACE] && !m_IsJumping)
		{
			m_Velocity.y += m_JumpSpeed;
			m_Smovement = SecondaryMovement::jump;
			m_IsJumping = true;
			SoundManager::PlaySoundEffect("Jump", false, true);
		}
		else if (m_IsJumping == true)
		{
			m_Smovement = SecondaryMovement::jump;
		}
		m_Velocity.y += m_Acceleration.y;

		if (pStates[SDL_SCANCODE_UP] && m_IsClimbing)
		{
			m_Smovement = SecondaryMovement::climbing;
			m_Velocity.y = 0;
			m_Velocity.y += 120;
		}
	}


	if (m_IsMoving == false)
	{
		m_Velocity.y -= 10.0f;
	}

	if (m_IsInEndLevel && pStates[SDL_SCANCODE_UP])
	{
		m_Lives = -100;
		m_HasCommitedSuicide = true;
	}
}

bool Player::SetMovement(bool isMoving)
{
	m_IsMoving = isMoving;

	return m_IsMoving;
}

bool Player::SetClimbing(bool isClimbing)
{
	m_IsClimbing = isClimbing;

	return m_IsClimbing;
}

void Player::SetPosition(const Point2f& playerPos)
{
	m_CollisonBox.left = playerPos.x;
	m_CollisonBox.bottom = playerPos.y;
}

void Player::SetEnding(bool isInEnd)
{
	m_IsInEndLevel = isInEnd;
}

Rectf Player::GetShape() const
{
	return m_CollisonBox;
}

void Player::AddCoin()
{
	++m_Coins;
}

void Player::SetSecondaryMovement(SecondaryMovement sMovement)
{
	m_Smovement = sMovement;
}

const int& Player::GetLives() const
{
	return m_Lives;
}

const int& Player::GetCoins() const
{
	return m_Coins;
}

void Player::SetLevelBeginPos(const Point2f& pos)
{
	m_BeginPosition = pos;
}

bool Player::m_IsCommitedSuicide() const
{
	if (m_HasCommitedSuicide)
	{
		return true;
	}
	return false;
}

void Player::StopSoundEffects(std::string name) const
{
	if (name != "Grass") SoundManager::StopSoundEffect("Grass");
}

Point2f Player::GetPosition() const
{
	return Point2f(m_CollisonBox.left, m_CollisonBox.bottom);
}
