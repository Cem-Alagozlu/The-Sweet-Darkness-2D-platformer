#include "stdafx.h"
#include "PlatformMoving.h"

PlatformMoving::PlatformMoving(const Point2f& position, const Point2f& endPos, float angle, float scale, int type)
	: Platform{position,"Resources/Images/Sprites/Levels/Platforms/platform03.png",angle,scale,"Resources/Images/Sprites/Levels/Platforms/platform03.svg"}
	  , m_EndPos{endPos}
	  , m_Type{type}
{
	m_BeginPos = m_Pos;
}

void PlatformMoving::Draw() const
{
	//utils::SetColor({ 1,0,0,1 });
	//utils::DrawPolygon(m_VerticesWorld);
	//utils::DrawPolygon(m_VerticesLocal);

	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, 0);
	glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
	glScalef(m_Scale, m_Scale, 1.0f);
	m_Texure.Draw({0.0f,0.0f});
	glPopMatrix();
}

void PlatformMoving::Update(float elapsedSec)
{
	UpdateVertices(Vector2f(0, 0));
	//Platform::UpdateVertices(Vector2f(m_Pos.x + m_Texure.GetWidth(), m_Pos.y + m_Texure.GetHeight()));


	if (m_Type == 1)
	{
		if (m_Pos.y >= m_EndPos.y)
		{
			m_Mover.y -= 5.0f;
		}
		else if (m_Pos.y <= m_BeginPos.y)
		{
			m_Mover.y += 5.0f;
		}
	}


	if (m_Type == 2)
	{
		if (m_Pos.x >= m_EndPos.x)
		{
			m_Mover.x -= 5.0f;
		}
		else if (m_Pos.x <= m_BeginPos.x)
		{
			m_Mover.x += 5.0f;
		}
	}


	m_Pos.y += m_Mover.y;
	m_Pos.x += m_Mover.x;
}

bool PlatformMoving::PlatformCollision(const Rectf& player)
{
	Rectf platform;
	platform.left = m_VerticesWorld[0].x;
	platform.bottom = m_VerticesWorld[2].y;
	platform.width = m_VerticesWorld[1].x - m_VerticesWorld[0].x;
	platform.height = m_VerticesWorld[0].y - m_VerticesWorld[2].y;


	return utils::IsOverlapping(platform, player);
}

void PlatformMoving::PlatformPlayerChange(Rectf& player) const
{
	player.left += m_Mover.x;
	player.bottom += m_Mover.y;
}
