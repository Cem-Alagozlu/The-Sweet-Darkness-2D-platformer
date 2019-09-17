#pragma once
#include "LevelManager.h"
#include "Player.h"
#include "LevelBase.h"

class LevelEnd : public LevelBase
{
public:
	//Constructor
	explicit LevelEnd(LevelManager& levelmanager, std::shared_ptr<Player> player, Game& game);
	LevelEnd(const LevelEnd&) = delete;
	LevelEnd& operator=(const LevelEnd&) = delete;

	//Draw level & update
	virtual void DrawFront() const override;
	virtual void Update(float elapsedSec) override;

	//Level functions
	virtual void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) override;
	virtual Rectf GetBoundaries() const override;

	//not needed
	virtual void DrawBack() const override;
	virtual void MouseMoved(const Point2f& mousePos) override;
	virtual void MouseClick(const SDL_MouseButtonEvent& e) override;
	virtual bool HasReachedEnd(const Rectf& actorShape) const override;
	virtual void DeathCollision() override;

private:
	Game& m_Game;
	std::unique_ptr<Texture> m_pLevelEndTexture;
	Texture m_FogFront;
	Texture m_End;
	float m_CamChangeX;
	float m_CamChangeY;

	Rectf m_FadeBox{0,0,9000,720};
	Rectf m_FadeBoxOut{0,0,9000,720};
	float m_Alpha{1.0f};

	// TECHNICAL STUFF
	Rectf m_Boundaries; // level width & height for camera matrix
	std::weak_ptr<Player> m_pPlayer;
	float m_PosX;
	float m_PosY;

	bool m_PhaseOne{true};
	bool m_PhaseTwo{false};
	bool m_IsButtonPressed{false};
};
