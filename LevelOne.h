#pragma once
#include "LevelManager.h"
#include "Player.h"
#include "LevelBase.h"
#include "TrapSpikeFall.h"
#include "TrapSwingBlade.h"
#include "PlatformStatic.h"
#include "LevelDecorations.h"
#include "Coin.h"

class LevelOne : public LevelBase
{
public:
	//Constructor
	explicit LevelOne(LevelManager& levelmanager, std::shared_ptr<Player> player);
	LevelOne(const LevelOne&) = delete;
	LevelOne& operator=(const LevelOne&) = delete;

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
	std::unique_ptr<Texture> m_pLevelOne00;
	std::unique_ptr<Texture> m_pLevelOne01;


	// INTRODUCTION & TUTORIAL & AMBIANCE
	std::vector<std::unique_ptr<Texture>> m_pTutorialTextures;
	const int m_imgAmount{9};// img -> introduction gremory // different shizzle names
	int m_imgNumber{};// amount for clicks
	std::shared_ptr<Mix_Chunk> m_pTrapSound01;

	// TECHNICAL STUFF
	Rectf m_Boundaries; // level width & height for camera matrix
	std::weak_ptr<Player> m_pPlayer;
	float m_PosX;
	float m_PosY;
	std::shared_ptr<Mix_Music> m_pMusicLevel01;
	Rectf m_EndRect{8835,80,400,180};
	bool m_IsInEndZone{false};
	float m_BeginCount{};
	float m_EndCount{5};

	// Trap, Obstacles, AI, etc.. Variables
	TrapSpikeFall m_TrapSpikeFall01;
	TrapSpikeFall m_TrapSpikeFall02;
	TrapSpikeFall m_TrapSpikeFall03;
	TrapSpikeFall m_TrapSpikeFall04;
	TrapSpikeFall m_TrapSpikeFall05;
	TrapSpikeFall m_TrapSpikeFall06;
	TrapSwingBlade m_TrapSwingBlade01;
	TrapSwingBlade m_TrapSwingBlade02;
	PlatformStatic m_Platform01;
	Rectf m_Pitfall01;
	Rectf m_Pitfall02;
	Rectf m_Pitfall03;
	std::vector<LevelDecorations> m_DecorationsFront;
	std::vector<LevelDecorations> m_DecorationsBack;
	std::vector<Coin> m_Coins;
	Texture m_EndingTexture;
};
