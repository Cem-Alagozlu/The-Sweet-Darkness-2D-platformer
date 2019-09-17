#pragma once
#include "LevelManager.h"
#include "Player.h"
#include "LevelBase.h"
#include "LevelDecorations.h"


class LevelBoss : public LevelBase
{
public:
	//Constructor
	explicit LevelBoss(LevelManager& levelmanager, std::shared_ptr<Player> player);
	LevelBoss(const LevelBoss&) = delete;
	LevelBoss& operator=(const LevelBoss&) = delete;

	//Draw level & update
	virtual void DrawFront() const override;
	virtual void DrawBack() const override;
	virtual void Update(float elapsedSec) override;
	void DrawHead() const;


	virtual void MouseMoved(const Point2f& mousePos) override;
	virtual void MouseClick(const SDL_MouseButtonEvent& e) override;
	virtual Rectf GetBoundaries() const override;
	virtual bool HasReachedEnd(const Rectf& actorShape) const override;
	virtual void DeathCollision() override;

	//Level functions
	virtual void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) override;
	void IntroText();

private:
	//TEXTURE
	//environement
	Texture m_LowerBodyBoss;
	Texture m_UpperBodyBoss;
	Texture m_FrontFog;
	Texture m_Sky;

	// TECHNICAL STUFF
	Rectf m_Boundaries; // level width & height for camera matrix
	std::weak_ptr<Player> m_pPlayer;
	float m_PosX;
	float m_PosY;
	bool m_IsPositive{true};
	float m_SwingBounderies;
	float m_Angle;


	Rectf m_FadeBox{0,0,1280,720};
	float m_Alpha{1.0f};
	bool m_IsFadeIN{false};

	std::vector<std::unique_ptr<Texture>> m_pExplaining;
	const int m_imgAmount{14};// img -> introduction gremory // different shizzle names
	int m_imgNumber{0};// amount for clicks

	float m_IntroTimer{};
	bool m_PhaseOne = false;
	bool m_IsLaserOn = false;
};
