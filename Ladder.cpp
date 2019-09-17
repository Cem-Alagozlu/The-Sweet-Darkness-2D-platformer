#include "stdafx.h"
#include "Ladder.h"
#include "Player.h"

Ladder::Ladder(const Point2f& pos, int type)
	: m_Pos{pos}
	  , m_Type{type}
	  , m_LadderKlein{"Resources/Images/Sprites/Extra/ladder_small.png"}
	  , m_LadderGroot{"Resources/Images/Sprites/Extra/ladder_big.png"}
	  , m_LadderMidden{"Resources/Images/Sprites/Extra/ladder_mid.png"}
{
	if (m_Type == 1)
	{
		m_LadderRect = Rectf{m_Pos.x + 80,m_Pos.y,m_LadderGroot.GetWidth() / 8 ,m_LadderGroot.GetHeight() - 50};
	}
	else if (m_Type == 2)
	{
		m_LadderRect = Rectf{m_Pos.x + 80,m_Pos.y,m_LadderMidden.GetWidth() / 8,m_LadderMidden.GetHeight() - 50};
	}
	else if (m_Type == 3)
	{
		m_LadderRect = Rectf{m_Pos.x + 80,m_Pos.y,m_LadderKlein.GetWidth() / 8,m_LadderKlein.GetHeight() - 50};
	}
}

Ladder::~Ladder()
{
}

void Ladder::Draw() const
{
	if (m_Type == 1)
	{
		m_LadderGroot.Draw(m_Pos);
	}
	else if (m_Type == 2)
	{
		m_LadderMidden.Draw(m_Pos);
	}
	else if (m_Type == 3)
	{
		m_LadderKlein.Draw(m_Pos);
	}
}

bool Ladder::Collision(Rectf& actorShape) const
{
	if (utils::IsOverlapping(m_LadderRect, actorShape))
	{
		return true;
	}
	return false;
}


void Ladder::SetLadderRect()
{
	if (m_Type == 1)
	{
		m_LadderRect = Rectf{m_Pos.x + 500 ,m_Pos.y,m_LadderGroot.GetWidth(),m_LadderGroot.GetHeight()};
	}
	else if (m_Type == 2)
	{
		m_LadderRect = Rectf{m_Pos.x + 500,m_Pos.y,m_LadderMidden.GetWidth(),m_LadderMidden.GetHeight()};
	}
	else if (m_Type == 3)
	{
		m_LadderRect = Rectf{m_Pos.x + 500,m_Pos.y,m_LadderKlein.GetWidth(),m_LadderKlein.GetHeight()};
	}
}
