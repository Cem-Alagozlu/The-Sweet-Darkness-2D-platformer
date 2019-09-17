#pragma once
class Lever
{
public:
	explicit Lever(const Point2f& pos, float angle, float scale);
	~Lever();

	void Draw() const;
	bool Collision(Rectf& actorShape) const;
	bool SetLeverPull(bool isPulled);

private:
	Point2f m_Pos;
	float m_Angle;
	float m_Scale;
	bool m_IsLeverPulled{false};

	Texture m_Lever01;
	Texture m_Lever02;
};
