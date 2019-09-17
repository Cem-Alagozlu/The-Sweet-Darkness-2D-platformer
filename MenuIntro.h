#pragma once
#include "Texture.h"
class Game;

class MenuIntro
{
public:
	MenuIntro(Game& game, bool playIntro);
	MenuIntro(const MenuIntro&) = delete;
	MenuIntro& operator=(const MenuIntro&) = delete;
	~MenuIntro() = default;

	void Update(float elapsedSec);
	void Draw() const;

private:

	// Data members
	Game& m_Game;
	Rectf m_FadeBox{0,0,1280,720};
	float m_Alpha{0.0f};

	bool m_IsFadeIN{true};

	int m_IndexAfbeeldingen{0};
	std::vector<std::shared_ptr<Texture>> m_Afbeeldingen;
};
