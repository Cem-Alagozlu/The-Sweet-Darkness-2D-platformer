#include "stdafx.h"
#include "TrapSwingBlade.h"
#include "SVGParser.h"
#include "SoundManager.h"

TrapSwingBlade::TrapSwingBlade(const Point2f& position, float angle, float scale, float swingBound)
	: Trap{position,"Resources/Images/Sprites/Levels/Obstacles/blade_swing01.png",angle,scale,"Resources/Images/Sprites/Levels/Obstacles/blade_swing01.svg"}
	  , m_SwingBounderies{swingBound}
{
}

void TrapSwingBlade::Draw() const
{
	glPushMatrix();
	glTranslatef(m_Pos.x, m_Pos.y, 0);
	glRotatef(m_Angle, 0.0f, 0.0f, 1.0f);
	glScalef(m_Scale, m_Scale, 1.0f);
	glTranslatef(-m_Texure.GetWidth() / 2, -m_Texure.GetHeight(), 0.0f);
	m_Texure.Draw({0.0f,0.0f});
	glPopMatrix();
}

void TrapSwingBlade::Update(float elapsedSec, const Vector2f& player)
{
	UpdateVertices(Vector2f(-m_Texure.GetWidth() / 2.0f, -m_Texure.GetHeight()));

	if (m_IsPositive == true)
	{
		++m_Angle;
	}
	else if (m_IsPositive == false)
	{
		--m_Angle;
	}

	if (m_Angle == -m_SwingBounderies)
	{
		m_IsPositive = true;
	}
	if (m_Angle >= m_SwingBounderies)
	{
		m_IsPositive = false;
	}

	SoundManager::PlaySoundEffectTraps(player, m_Pos, "Blade", true, true);
	SoundManager::Update(player, m_Pos, "Blade");
}

bool TrapSwingBlade::BladeCollision(const Rectf& player) const
{
	return utils::IsOverlapping(m_VerticesWorld, player);
}
