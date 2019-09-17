#pragma once
#include "LevelManager.h"
#include "Player.h"

class LevelBase
{
public:
	explicit LevelBase(LevelManager& levelmanager, const std::string& path);
	LevelBase(const LevelBase&) = delete;
	LevelBase& operator=(const LevelBase&) = delete;
	virtual ~LevelBase() = default;

	virtual void DrawFront() const = 0;
	virtual void DrawBack() const = 0;
	virtual void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity);
	virtual void Update(float elapsedSec) = 0;

	virtual void MouseMoved(const Point2f& mousePos) = 0;
	virtual void MouseClick(const SDL_MouseButtonEvent& e) = 0;

	virtual Rectf GetBoundaries() const = 0;
	virtual bool HasReachedEnd(const Rectf& actorShape) const;
	virtual void DeathCollision() = 0;

	bool IsOnGround(Rectf& actorShape, Vector2f& actorVelocity) const;
	virtual Point2f GetBeginPos() const;

protected:

	Point2f m_BeginPos;


	LevelManager& m_LevelManager;

	std::vector<Point2f> m_Vertices;
	void SetPos(float x, float y);

	//Textures
	std::unique_ptr<Texture> m_pBackMist;
	std::unique_ptr<Texture> m_pTrees00;
	std::unique_ptr<Texture> m_pTrees01;
	std::unique_ptr<Texture> m_pTrees02;
	std::unique_ptr<Texture> m_pFrontMist01;
	Texture m_LoadingScreen;
};
