#include "stdafx.h"
#include "LevelOne.h"
#include "SVGParser.h"
#include "Player.h"
#include <sstream>
#include "SoundManager.h"

LevelOne::LevelOne(LevelManager& levelmanager, std::shared_ptr<Player> player)
	: LevelBase{levelmanager,"Resources/Images/Sprites/Levels/Level_One/levelone01.svg"}
	  , m_pPlayer{player}
	  , m_TrapSpikeFall01{{2310.0f,400.0f}, 0.0f, 1.0f, 10.0f,false}
	  , m_TrapSpikeFall02{{1500.0f,400.0f}, 0.0f, 1.0f, 40.0f,false}
	  , m_TrapSpikeFall03{{6150.0f,400.0f}, 0.0f, 1.0f, 65.0f,false}
	  , m_TrapSpikeFall04{{6600.0f,400.0f}, 0.0f, 1.0f, 70 ,false}
	  , m_TrapSpikeFall05{{6800,400.0f}, 0.0f, 1.0f, 80,false}
	  , m_TrapSpikeFall06{{7000,400.0f}, 0.0f, 1.0f, 90 ,false}
	  , m_TrapSwingBlade01{{4445.0f,720.0f},0.0f,0.75f,180.0f}
	  , m_TrapSwingBlade02{{5445.0f,750.0f},0.0f,0.50f,100.0f}
	  , m_Platform01{{8150.0f,200.0f},"Resources/Images/Sprites/Levels/Platforms/platform01.png",0.0f,1.0f,"Resources/Images/Sprites/Levels/Platforms/platform01.svg"}
	  , m_Pitfall01{3120.0f,0.0f,350.0f,115.0f}
	  , m_Pitfall02{5710.0f,0.0f,290.0f,50.0f}
	  , m_Pitfall03{7900.0f,0.0f,750,115.0f}
	  , m_EndingTexture{"Resources/Images/Sprites/Extra/load.png"}
{
	InitEnvironement();
	InitializeCoins();
	//Initialize collision for level one

	m_pMusicLevel01 = std::shared_ptr<Mix_Music>(Mix_LoadMUS("Resources/Sound/Music/StoryLevel.mp3"), [](Mix_Music* track) { Mix_FreeMusic(track); });
	//Values given to boundaries of level one
	m_Boundaries = {0,0,m_pLevelOne00->GetWidth(),m_pLevelOne00->GetHeight()};

	//Initialize img's for beginning speech & tutorial
	for (int idx = 0; idx < m_imgAmount; ++idx)
	{
		std::stringstream str;
		str << "Resources/Images/Storyline/tutorial/" << idx + 1 << ".png";
		m_pTutorialTextures.push_back(std::make_unique<Texture>(str.str()));
	}

	m_BeginPos = Point2f{30,30};
}

void LevelOne::InitializeCoins()
{
	m_Coins.push_back(Coin(Point2f{1650,160.0f}));
	m_Coins.push_back(Coin(Point2f{1700,160.0f}));
	m_Coins.push_back(Coin(Point2f{1750,160.0f}));
	m_Coins.push_back(Coin(Point2f{1800,160.0f}));
	m_Coins.push_back(Coin(Point2f{1850,160.0f}));
	m_Coins.push_back(Coin(Point2f{1900,160.0f}));
	m_Coins.push_back(Coin(Point2f{1950,160.0f}));
	m_Coins.push_back(Coin(Point2f{2000,160.0f}));


	m_Coins.push_back(Coin(Point2f{2500,50}));
	m_Coins.push_back(Coin(Point2f{2600,100}));
	m_Coins.push_back(Coin(Point2f{2700,150}));
	m_Coins.push_back(Coin(Point2f{2800,200}));
	m_Coins.push_back(Coin(Point2f{2900,250}));
	m_Coins.push_back(Coin(Point2f{3000,300}));

	m_Coins.push_back(Coin(Point2f{3400,300}));
	m_Coins.push_back(Coin(Point2f{3500,250}));
	m_Coins.push_back(Coin(Point2f{3600,200}));
	m_Coins.push_back(Coin(Point2f{3700,150}));
	m_Coins.push_back(Coin(Point2f{3800,100}));
	m_Coins.push_back(Coin(Point2f{3900,50}));
}

void LevelOne::DrawFront() const
{
	m_pLevelOne01->Draw(Rectf{0,0,9000,1000});
	m_Platform01.Draw();

	if (m_imgNumber <= 4 && m_imgNumber >= 0)
	{
		m_pTutorialTextures[m_imgNumber]->Draw(Rectf{0,0,1280,720});
	}

	if (m_imgNumber == 6)
	{
		m_pTutorialTextures[m_imgNumber]->Draw(Rectf{580,0,1280,720});
	}

	for (const LevelDecorations& decoration : m_DecorationsFront)
	{
		decoration.Draw();
	}

	for (size_t i = 0; i < m_Coins.size(); i++)
	{
		m_Coins[i].Draw();
	}

	if (m_imgNumber == 8)
	{
		m_pTutorialTextures[m_imgNumber]->Draw(Rectf{3110 ,0,1280,720});
	}
	if (m_IsInEndZone)
	{
		m_EndingTexture.Draw({7720,0,1280,720});
	}

	DrawTraps();
}

void LevelOne::DrawBack() const
{
	m_pBackMist->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8,0,9000,1000});// background mist moving 01
	m_pTrees01->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 6 ,0,9000,1000});// background trees01 moving 02
	m_pTrees00->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8 ,0,9000,1000});// background trees00 moving 03
	m_pTrees02->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8,0,9000,1000});// background trees02 moving 04

	for (const LevelDecorations& decoration : m_DecorationsBack)
	{
		decoration.Draw();
	}
}

void LevelOne::DrawTraps() const
{
	m_TrapSpikeFall01.Draw();
	m_TrapSpikeFall02.Draw();
	m_TrapSpikeFall03.Draw();
	m_TrapSpikeFall04.Draw();
	m_TrapSpikeFall05.Draw();
	m_TrapSpikeFall06.Draw();
	m_TrapSwingBlade01.Draw();
	m_TrapSwingBlade02.Draw();
}

void LevelOne::Update(float elapsedSec)
{
	//player pos
	m_PosX = m_pPlayer.lock()->GetShape().left;
	m_PosY = m_pPlayer.lock()->GetShape().bottom;

	if (m_PosX >= 1132.19f && m_imgNumber == 5)
	{
		m_imgNumber = 6;
		m_pPlayer.lock()->SetMovement(false);
	}

	if (m_PosX >= 3660 && m_imgNumber == 7)
	{
		m_imgNumber = 8;
		m_pPlayer.lock()->SetMovement(false);
	}
	if (m_IsInEndZone)
	{
		m_BeginCount = m_BeginCount + elapsedSec;
	}

	m_TrapSpikeFall01.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall02.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall03.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall04.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall05.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall06.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSwingBlade01.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSwingBlade02.Update(elapsedSec, m_pPlayer.lock()->GetPosition());

	for (size_t i = 0; i < m_Coins.size(); i++)
	{
		m_Coins[i].Update(elapsedSec);
	}
}

void LevelOne::MouseMoved(const Point2f& mousePos)
{
}

void LevelOne::MouseClick(const SDL_MouseButtonEvent& e)
{
	if (m_imgNumber <= 4 && m_imgNumber >= 0)
	{
		m_imgNumber++;
	}

	if (m_imgNumber == 5 || m_imgNumber == 6 || m_imgNumber == 8)
	{
		m_pPlayer.lock()->SetMovement(true);
	}

	if (m_imgNumber == 6)
	{
		m_imgNumber = 7;
	}

	if (m_imgNumber == 8)
	{
		m_imgNumber = 9;
	}
}

void LevelOne::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	LevelBase::HandleCollision(actorShape, actorVelocity);
	DeathCollision();

	m_Platform01.HandleCollision(actorShape, actorVelocity);


	for (size_t i = 0; i < m_Coins.size(); i++)
	{
		if (m_Coins[i].IsOverlapping(actorShape))
		{
			m_Coins[i].PlayCoinSound();
			m_pPlayer.lock()->AddCoin();
			m_Coins.erase(m_Coins.begin() + i);
		}
	}

	if (utils::IsOverlapping(m_EndRect, actorShape))
	{
		m_pPlayer.lock()->SetMovement(false);
		m_IsInEndZone = true;
	}
	else
	{
		m_IsInEndZone = false;
	}

	if (m_BeginCount >= m_EndCount)
	{
		SoundManager::PlaySoundEffect("Teleport", false, true);
		m_LevelManager.SetCurrentLevel(LevelManager::Level::levelTwo);
	}
}

Rectf LevelOne::GetBoundaries() const
{
	return m_Boundaries;
}

void LevelOne::DeathCollision()
{
	if (m_TrapSpikeFall01.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall02.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall03.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall04.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall05.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall06.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSwingBlade01.BladeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSwingBlade02.BladeCollision(m_pPlayer.lock()->GetShape())
		|| utils::IsOverlapping(m_Pitfall01, m_pPlayer.lock()->GetShape())
		|| utils::IsOverlapping(m_Pitfall02, m_pPlayer.lock()->GetShape())
		|| utils::IsOverlapping(m_Pitfall03, m_pPlayer.lock()->GetShape()))
	{
		m_pPlayer.lock()->SetSecondaryMovement(Character::SecondaryMovement::death);
	}
}

void LevelOne::InitEnvironement()
{
	//Initialize environement
	m_pLevelOne00 = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Level_One/levelone00.png");
	m_pLevelOne01 = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Level_One/levelone01.png");

	//back decorations
	m_DecorationsBack.push_back(LevelDecorations{"tree01",{-90.0f,-20.0f},1.0f,1.0f});
	m_DecorationsBack.push_back(LevelDecorations{"tree02",{-490.0f,-20.0f},1.0f,1.0f});
	m_DecorationsBack.push_back(LevelDecorations{"chain",{50,600.0f},0.75f,1.0f});
	m_DecorationsBack.push_back(LevelDecorations{"chain",{90,600.0f},0.75f,1.0f});

	//front decorations
	m_DecorationsFront.push_back(LevelDecorations{"fence03",{2435.0f ,40.0f},0.75f,1.0f});
	m_DecorationsFront.push_back(LevelDecorations{"arrow",{90.0f ,70.0f},1,1.0f});
	m_DecorationsFront.push_back(LevelDecorations{"start",{70 ,680},0.55f,1.0f});
}
