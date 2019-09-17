#pragma once
class LevelBase;
#include "Character.h"
#include "Sprite.h"

class Player : public Character
{
public:
	Player();
	Player(Player& other) = delete;
	Player(Player&& other) = delete;
	Player operator=(Player& rhs) = delete;
	Player operator=(Player&& rhs) = delete;
	virtual ~Player();


	virtual void Update(float elapsedSec, std::shared_ptr<LevelBase> level) override;
	void UpdateSprite(float elapsedSec);
	void UpdatePosition(float elapsedSec);
	void UpdateCollision(std::shared_ptr<LevelBase> level);
	void UpdateReset(float elapsedSec);

	void Draw() const override;
	void DrawDebugHelp() const;

	bool SetMovement(bool isMoving);
	bool SetClimbing(bool isClimbing);
	void SetPosition(const Point2f& playerPos);
	void SetEnding(bool isInEnd);
	Point2f GetPosition() const;
	Rectf GetShape() const;
	void AddCoin();
	void SetSecondaryMovement(SecondaryMovement sMovement);
	const int& GetLives() const;
	const int& GetCoins() const;

	void SetLevelBeginPos(const Point2f& pos);

	bool m_IsMoving;
	bool m_IsCommitedSuicide() const;
	void StopSoundEffects(std::string name) const;
private:
	Sprite m_Jump;
	Sprite m_Idle;
	Sprite m_Walk;
	Sprite m_Death;
	Sprite m_Climbing;
	Sprite m_Suicide;
	Sprite* m_pCurrentSprite;

	int m_Lives{10};
	int m_Coins{0};

	float m_Width;
	float m_Height;
	Vector2f m_Acceleration{0,-9.81f};
	const float m_HorSpeed{250.0f};//225.0f
	const float m_JumpSpeed{450.0f};//800.0f
	Vector2f m_Velocity{0.0f,0.0f};
	bool m_IsJumping{false};
	bool m_IsClimbing{false};
	bool m_HasPlayedDeathSound{false};
	bool m_HasCommitedSuicide{false};
	bool m_IsInEndLevel{false};
	const float m_TotalTimerReset{1.0f};
	float m_TotalAccum{};

	void HandleMoveKeysState(float elapsedSec);


	Point2f m_BeginPosition;
};
