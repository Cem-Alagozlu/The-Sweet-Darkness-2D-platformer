#pragma once
#include "LevelManager.h"

class Credits
{
public:
	//Constructor niet kopieer-baar
	explicit Credits(Game& game);
	Credits(const Credits&) = delete;
	Credits& operator=(const Credits&) = delete;


	void DrawFront() const;
	void Update(float elapsedSec);

	//Player input
	void MouseClick(const SDL_MouseButtonEvent& e) const;


private:
	std::vector<std::unique_ptr<Texture>> m_Credits;
	const int m_imgAmount{8};// img -> aantal
	Game& m_Game;

	Rectf m_FadeBox{0,0,1280,720};
	float m_Alpha{0.0f};
	int m_IndexAfbeeldingen{0};
	bool m_IsFadeIN{true};
};
