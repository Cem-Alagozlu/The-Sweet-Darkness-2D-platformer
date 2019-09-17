#pragma once
#include "Texture.h"

class LevelDecorations
{
public:
	explicit LevelDecorations(const std::string& name, const Point2f& position, float scale, float rotate);
	LevelDecorations(const LevelDecorations&) = default;
	LevelDecorations& operator=(const LevelDecorations&) = default;
	~LevelDecorations() = default;

	void Draw() const;

private:
	std::shared_ptr<Texture> m_Texture;
	Point2f m_Pos;
	float m_Scale;
	float m_Rotation;

	void Init(const std::string& name);
};
