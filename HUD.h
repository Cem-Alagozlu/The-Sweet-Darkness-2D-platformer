#pragma once
#include "Sprite.h"

class HUD
{
public:
	HUD(const int& life, const int& coins);
	~HUD();

	void Draw() const;
	void Update(float elapsedSec);


private:
	const int& m_LifeCounter;
	int m_PreviousLCounter;

	const int& m_CoinCounter;
	int m_PreviousCCounter{-1};


	Texture m_NameTexture01;
	Texture m_NameTexture02;
	Texture m_CoinTexture;

	std::unique_ptr<Texture> m_LifeCounterTexture;
	std::unique_ptr<Texture> m_CoinCounterTexture;
};
