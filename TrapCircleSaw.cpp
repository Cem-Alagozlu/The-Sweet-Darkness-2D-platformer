#include "stdafx.h"
#include "TrapCircleSaw.h"

TrapCircleSaw::TrapCircleSaw(const Point2f& position, float scale)
	: Trap{position,"Resources/Images/Sprites/Levels/Obstacles/saw1.png",m_Angle,scale,""}
{
	m_Shape.center.x = m_Pos.x + m_Texure.GetWidth() / 2;
	m_Shape.center.y = m_Pos.y + m_Texure.GetHeight() / 2;
	m_Shape.radius = 320 * m_Scale;
}

void TrapCircleSaw::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Shape.center.x, m_Shape.center.y, 0);
	glRotatef(m_Angle, 0, 0, 1);
	glScalef(m_Scale, m_Scale, 1.0f);
	glTranslatef(-m_Texure.GetWidth() / 2, -m_Texure.GetHeight() / 2, 0);
	m_Texure.Draw({0,0});
	glPopMatrix();
}

void TrapCircleSaw::Update(float elapsedSec, const Vector2f& player)
{
	m_Angle += 2;
}

bool TrapCircleSaw::CircleCollision(const Rectf& rect) const
{
	if (utils::IsOverlapping(rect, m_Shape))
	{
		std::cout << "death" << std::endl;
		return true;
	}
	return false;
}
