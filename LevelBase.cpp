#include "stdafx.h"
#include "SVGParser.h"
#include "LevelBase.h"


LevelBase::LevelBase(LevelManager& levelManager, const std::string& path)
	: m_LevelManager{levelManager}
	  , m_LoadingScreen("Resources/Images/Sprites/Extra/load.png")
{
	m_pBackMist = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Level_One/backmist.png");
	m_pTrees00 = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Level_One/trees00.png");
	m_pTrees01 = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Level_One/trees01.png");
	m_pTrees02 = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Level_One/trees02.png");
	m_pFrontMist01 = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Level_One/fog_front.png");

	SVGParser::GetVerticesFromSvgFile(path, m_Vertices);
}

bool LevelBase::IsOnGround(Rectf& actorShape, Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo;
	Point2f actorTopPos{actorShape.left + actorShape.width / 2, actorShape.height + actorShape.bottom};
	bool hit = Raycast(m_Vertices, actorTopPos, {actorTopPos.x, actorTopPos.y - actorShape.height - 1.0f}, hitInfo);
	return hit;
}


bool LevelBase::HasReachedEnd(const Rectf& actorShape) const
{
	return false;
}

Point2f LevelBase::GetBeginPos() const
{
	return m_BeginPos;
}

void LevelBase::SetPos(float x, float y)
{
	m_BeginPos.x = x;
	m_BeginPos.y = y;
}

void LevelBase::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	utils::HitInfo hitInfo;
	Point2f actorBottomPos{actorShape.left + actorShape.width / 2, actorShape.bottom};
	Point2f actorTopPos{actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height};
	bool hit = Raycast(m_Vertices, actorBottomPos, actorTopPos, hitInfo);
	if (hit)
	{
		actorShape.bottom = hitInfo.intersectPoint.y;
		if (actorVelocity.y <= 0)
		{
			actorVelocity.y = 0;
		}
	}

	Point2f actorLeftPos{actorShape.left , actorShape.bottom + actorShape.height / 2};
	Point2f actorRightPos{actorShape.left + actorShape.width , actorShape.bottom + actorShape.height / 2};

	hit = Raycast(m_Vertices, actorLeftPos, actorRightPos, hitInfo);
	if (hit)
	{
		if (hitInfo.normal.x > 0)
		{
			actorShape.left = hitInfo.intersectPoint.x;
		}
		else
		{
			actorShape.left = hitInfo.intersectPoint.x - actorShape.width - 1;
		}
		actorVelocity.x = 0.0f;
	}
}
