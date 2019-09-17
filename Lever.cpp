#include "stdafx.h"
#include "Lever.h"


Lever::Lever(const Point2f& pos, float angle, float scale)
	: m_Pos{pos}
	  , m_Angle{angle}
	  , m_Scale{scale}
	  , m_Lever01{"Resources/Images/Sprites/Extra/lever1.png"}
	  , m_Lever02{"Resources/Images/Sprites/Extra/lever2.png"}
{
}

Lever::~Lever()
{
}

void Lever::Draw() const
{
	if (m_IsLeverPulled)
	{
		glPushMatrix();
		glTranslatef(m_Pos.x, m_Pos.y, 0);
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
		glScalef(m_Scale, m_Scale, 1.0f);
		m_Lever02.Draw({0.0f,0.0f});
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
		glTranslatef(m_Pos.x, m_Pos.y, 0);
		glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
		glScalef(m_Scale, m_Scale, 1.0f);
		m_Lever01.Draw({0.0f,0.0f});
		glPopMatrix();
	}
}

bool Lever::Collision(Rectf& actorShape) const
{
	Rectf LeverRect{m_Pos.x + 10, m_Pos.y + 40,160,200};

	if (utils::IsOverlapping(LeverRect, actorShape))
	{
		return true;
	}
	return false;
}

bool Lever::SetLeverPull(bool isPulled)
{
	return m_IsLeverPulled = isPulled;
}
