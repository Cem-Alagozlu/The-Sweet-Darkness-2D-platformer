#pragma once
#include "LevelManager.h"
#include "Player.h"
#include "LevelBase.h"
#include "TrapSpikeFall.h"
#include "TrapCircleSaw.h"
#include "TrapSwingBlade.h"
#include "PlatformStatic.h"
#include "PlatformMoving.h"
#include "LevelDecorations.h"
#include "Coin.h"
#include "Ladder.h"
#include "Lever.h"

class LevelFour : public LevelBase
{
public:
	//Constructor
	explicit LevelFour(LevelManager& levelmanager, std::shared_ptr<Player> player);
	LevelFour(const LevelFour&) = delete;
	LevelFour& operator=(const LevelFour&) = delete;

	void InitializeCoins();

	//Draw level & update
	virtual void DrawFront() const override;
	virtual void DrawBack() const override;
	virtual void Update(float elapsedSec) override;
	void DrawTraps() const;

	//Player input
	virtual void MouseMoved(const Point2f& mousePos) override;
	virtual void MouseClick(const SDL_MouseButtonEvent& e) override;

	//Level functions
	virtual void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) override;
	virtual Rectf GetBoundaries() const override;
	virtual void DeathCollision() override;

private:
	// TEXTURES FOR LEVEL
	// environement in smart pointers
	void InitEnvironement();
	std::unique_ptr<Texture> m_pLevelFour00;

	// TECHNICAL STUFF
	Rectf m_Boundaries; // level width & height for camera matrix
	std::weak_ptr<Player> m_pPlayer;
	float m_PosX;
	float m_PosY;

	//ladders
	Ladder m_Ladder01;
	Ladder m_Ladder02;
	Ladder m_Ladder03;
	Ladder m_Ladder04;
	Ladder m_Ladder05;
	Ladder m_Ladder06;
	Ladder m_Ladder07;
	Ladder m_Ladder08;
	Ladder m_Ladder09;
	Ladder m_Ladder10;
	Ladder m_Ladder11;
	Ladder m_Ladder12;
	Ladder m_Ladder13;
	Ladder m_Ladder14;

	PlatformMoving m_PlatformMoving01;
	PlatformMoving m_PlatformMoving02;
	PlatformMoving m_PlatformMoving03;
	PlatformMoving m_PlatformMoving04;
	PlatformMoving m_PlatformMoving05;
	PlatformMoving m_PlatformMoving06;
	PlatformMoving m_PlatformMoving07;
	PlatformMoving m_PlatformMoving08;


	PlatformStatic m_Platform01;
	PlatformStatic m_Platform02;
	PlatformStatic m_Platform03;
	PlatformStatic m_Platform04;
	PlatformStatic m_Platform05;
	PlatformStatic m_Platform06;

	std::vector<LevelDecorations> m_DecorationsFront;
	std::vector<LevelDecorations> m_DecorationsBack;
	std::vector<Coin> m_Coins;

	//TRAPS
	//Circle Saw
	TrapCircleSaw m_CircleSaw01;
	TrapCircleSaw m_CircleSaw02;
	TrapCircleSaw m_CircleSaw03;
	TrapCircleSaw m_CircleSaw04;
	TrapCircleSaw m_CircleSaw05;
	TrapCircleSaw m_CircleSaw06;
	TrapCircleSaw m_CircleSaw07;
	TrapCircleSaw m_CircleSaw08;
	TrapCircleSaw m_CircleSaw09;
	TrapCircleSaw m_CircleSaw10;
	TrapCircleSaw m_CircleSaw11;

	//Trap Spike fall
	TrapSpikeFall m_TrapSpikeFall01;
	TrapSpikeFall m_TrapSpikeFall02;

	//Trap Blade Swing
	TrapSwingBlade m_TrapBladeSwing01;

	Rectf m_Pitfall01;
	Rectf m_Pitfall02;

	Texture m_BigTree01;
	Texture m_LeverTexture;
	Lever m_Lever01;
	Rectf m_KillThePlayer;
	bool m_IsLeverPulled{false};


	Rectf m_EndRect{8570,440,400,120};
	bool m_IsInEndZone{false};
	float m_EndCount{5};
	float m_BeginCount{};
};
