#pragma once
#include "Trap.h"

class TrapCircleSaw : public Trap
{
public:
	TrapCircleSaw(const Point2f& position, float scale);
	TrapCircleSaw(const TrapCircleSaw&) = delete;
	TrapCircleSaw& operator=(const TrapCircleSaw&) = delete;
	virtual ~TrapCircleSaw() = default;

	virtual void Draw() const override;
	virtual void Update(float elapsedSec, const Vector2f& player) override;

	bool CircleCollision(const Rectf& rect) const;

private:
	float m_Angle{0};
	Circlef m_Shape;
};
