#pragma once
#include "LevelManager.h"
#include "Player.h"
#include "LevelBase.h"
#include "TrapSpikeFall.h"
#include "TrapCircleSaw.h"
#include "TrapSwingBlade.h"
#include "PlatformStatic.h"
#include "LevelDecorations.h"
#include "Coin.h"
#include "Ladder.h"

class LevelTwo : public LevelBase
{
public:
	//Constructor
	explicit LevelTwo(LevelManager& levelmanager, std::shared_ptr<Player> player);
	LevelTwo(const LevelTwo&) = delete;
	LevelTwo& operator=(const LevelTwo&) = delete;

	void InitializeCoins();

	//Draw level & update
	virtual void DrawFront() const override;
	virtual void DrawBack() const override;
	virtual void Update(float elapsedSec) override;
	void DrawTraps() const;

	virtual void MouseMoved(const Point2f& mousePos) override;
	virtual void MouseClick(const SDL_MouseButtonEvent& e) override;


	//Level functions
	virtual void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) override;
	virtual Rectf GetBoundaries() const override;
	virtual void DeathCollision() override;
	virtual Point2f GetBeginPos() const override;


private:
	// TEXTURES FOR LEVEL
	// environement in smart pointers
	void InitEnvironement();
	std::unique_ptr<Texture> m_pLevelTwo00;


	// Trap, Obstacles, AI, etc.. Variables
	TrapSpikeFall m_TrapSpikeFall01;
	TrapSpikeFall m_TrapSpikeFall02;
	TrapSpikeFall m_TrapSpikeFall03;
	TrapSpikeFall m_TrapSpikeFall04;
	TrapCircleSaw m_CircleSaw01;
	TrapCircleSaw m_CircleSaw02;
	TrapCircleSaw m_CircleSaw03;
	TrapSwingBlade m_TrapSwingBlade02;
	TrapSwingBlade m_TrapSwingBlade03;
	PlatformStatic m_Platform01;
	Rectf m_Pitfall01;
	Rectf m_Pitfall02;
	Rectf m_Pitfall03;
	Rectf m_Pitfall04;
	Ladder m_Ladder01;

	// TECHNICAL STUFF
	Rectf m_Boundaries; // level width & height for camera matrix
	std::weak_ptr<Player> m_pPlayer;
	float m_PosX;
	float m_PosY;

	Rectf m_EndRect{8800,390,400,120};
	bool m_IsInEndZone{false};
	float m_BeginCount{};
	float m_EndCount{5};

	std::vector<LevelDecorations> m_DecorationsFront;
	std::vector<LevelDecorations> m_DecorationsBack;
	std::vector<Coin> m_Coins;
};
