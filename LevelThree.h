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
#include "Lever.h"

class LevelThree : public LevelBase
{
public:
	//Constructor
	explicit LevelThree(LevelManager& levelmanager, std::shared_ptr<Player> player);
	LevelThree(const LevelThree&) = delete;
	LevelThree& operator=(const LevelThree&) = delete;

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
	void CutSceneLever();


private:
	// TEXTURES FOR LEVEL
	// environement in smart pointers
	void InitEnvironement();
	std::unique_ptr<Texture> m_pLevelThree00;

	// Trap, Obstacles, AI, etc.. Variables
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
	Ladder m_Ladder15;
	Ladder m_Ladder16;
	Ladder m_Ladder17;
	Ladder m_Ladder18;
	Ladder m_Ladder19;
	Ladder m_Ladder20;

	TrapSwingBlade m_TrapSwingBlade01;
	TrapSwingBlade m_TrapSwingBlade02;
	TrapSwingBlade m_TrapSwingBlade03;

	TrapCircleSaw m_TrapCircleSaw01;
	TrapCircleSaw m_TrapCircleSaw02;
	TrapCircleSaw m_TrapCircleSaw03;
	TrapCircleSaw m_TrapCircleSaw04;
	TrapCircleSaw m_TrapCircleSaw05;
	TrapCircleSaw m_TrapCircleSaw06;
	TrapCircleSaw m_TrapCircleSaw07;

	TrapSpikeFall m_TrapSpikeFall01;
	TrapSpikeFall m_TrapSpikeFall02;
	TrapSpikeFall m_TrapSpikeFall03;
	TrapSpikeFall m_TrapSpikeFall04;
	TrapSpikeFall m_TrapSpikeFall05;

	Rectf m_Pitfall01;
	Rectf m_Pitfall02;
	Rectf m_Pitfall03;
	Rectf m_KillThePlayer;

	Texture m_BigTree01;
	Lever m_Lever01;
	PlatformStatic m_Platform01;

	// TECHNICAL STUFF
	Rectf m_Boundaries; // level width & height for camera matrix

	float m_CamChangeX;
	float m_CamChangeY;
	float m_BigTreeChangeY{-20};
	float m_Subtractor{0};
	std::weak_ptr<Player> m_pPlayer;
	float m_PosX;
	float m_PosY;
	Rectf m_EndRect{8770,1760,400,120};
	bool m_IsInEndZone{false};
	float m_EndCount{5};
	float m_BeginCount{};
	Rectf m_Teleport{3700,1750,100,400};

	// INTRODUCTION & TUTORIAL & AMBIANCE
	std::vector<std::unique_ptr<Texture>> m_pExplaining;
	const int m_imgAmount{6};// img -> introduction gremory // different shizzle names
	int m_imgNumber{};// amount for clicks

	bool m_IsCutScenePassed{false};
	bool m_IsLeverPulled{false};
	bool m_IsTeleporting{false};

	std::vector<LevelDecorations> m_DecorationsFront;
	std::vector<LevelDecorations> m_DecorationsBack;
	std::vector<Coin> m_Coins;
};
