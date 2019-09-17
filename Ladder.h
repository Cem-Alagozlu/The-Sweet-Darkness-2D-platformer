#pragma once
class Ladder
{
public:
	explicit Ladder(const Point2f& pos, int type);
	~Ladder();

	void Draw() const;
	bool Collision(Rectf& actorShape) const;
	void SetLadderRect();

private:
	Point2f m_Pos;
	int m_Type;
	Rectf m_LadderRect;


	Texture m_LadderKlein;
	Texture m_LadderGroot;
	Texture m_LadderMidden;
};
