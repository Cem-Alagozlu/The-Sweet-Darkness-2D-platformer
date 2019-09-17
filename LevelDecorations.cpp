#include "stdafx.h"
#include "LevelDecorations.h"

LevelDecorations::LevelDecorations(const std::string& name, const Point2f& position, float scale, float rotate)
	: m_Pos(position)
	  , m_Scale(scale)
	  , m_Rotation(rotate)
{
	Init(name);
}

void LevelDecorations::Draw() const
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0);
	glRotatef(m_Rotation, 0.0f, 0.0f, 1.0f);
	glScalef(m_Scale, m_Scale, 1.0f);
	m_Texture->Draw(m_Pos);
	glPopMatrix();
}


void LevelDecorations::Init(const std::string& name)
{
	if (name == "fence01") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/fence01.png");
	else if (name == "fence02") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/fence02.png");
	else if (name == "fence03") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/fence03.png");

	else if (name == "cross01") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/cross01.png");
	else if (name == "cross02") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/cross02.png");
	else if (name == "cross03") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/cross03.png");

	else if (name == "fog01") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/fog01.png");
	else if (name == "fog02") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/fog02.png");

	else if (name == "tree01") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/tree01.png");
	else if (name == "tree02") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/tree02.png");

	else if (name == "moon") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/moon.png");
	else if (name == "chain") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/chain.png");
	else if (name == "arrow") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/arrow.png");
	else if (name == "start") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/start.png");
	else if (name == "end") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/end.png");
	else if (name == "platform01") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/1.png");
	else if (name == "platform02") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/2.png");
	else if (name == "platform03") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/3.png");
	else if (name == "kolom01") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/kolom01.png");
	else if (name == "roots1") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/roots1.png");
	else if (name == "gear1") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/gear1.png");
	else if (name == "ground01") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/ground01.png");
	else if (name == "ground02") m_Texture = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Decoration/ground02.png");

	else
	{
		std::cout << "Texture file name is wrong. " << name << std::endl;
	}
}
