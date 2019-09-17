#pragma once
#include "Platform.h"


class PlatformMoving : public Platform
{
public:
	PlatformMoving(const Point2f& position, const Point2f& endPos, float angle, float scale, int type);
	PlatformMoving(const PlatformMoving&) = delete;
	PlatformMoving& operator=(const PlatformMoving&) = delete;
	virtual ~PlatformMoving() = default;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec) override;

	bool PlatformCollision(const Rectf& player);
	void PlatformPlayerChange(Rectf& player) const;

private:
	std::string m_PathSVG;
	Point2f m_Mover;
	Point2f m_BeginPos;
	Point2f m_EndPos;

	int m_Type;
};
