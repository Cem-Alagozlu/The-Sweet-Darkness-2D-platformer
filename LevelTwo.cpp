#include "stdafx.h"
#include "LevelTwo.h"
#include "SVGParser.h"
#include "Player.h"
#include "SoundManager.h"


LevelTwo::LevelTwo(LevelManager& levelmanager, std::shared_ptr<Player> player)
	: LevelBase{levelmanager,"Resources/Images/Sprites/Levels/Level_Two/leveltwo02.svg"}
	  , m_TrapSpikeFall01{{490,0},0,1,140,true}
	  , m_TrapSpikeFall02{{5940,0},0,1,140,true}
	  , m_TrapSpikeFall03{{7268.0f,400.0f},0,1,80,false}
	  , m_TrapSpikeFall04{{8400,900},0,1,80,false}
	  , m_CircleSaw01{{2750,-375},0.35f}
	  , m_CircleSaw02{{3200,-475},0.35f}
	  , m_CircleSaw03{{7268,-475},0.35f}
	  , m_TrapSwingBlade02{{2200, 0}, 0, 0.45f, 360}
	  , m_TrapSwingBlade03{{5350, 0}, 0, 0.50f, 360}
	  , m_Platform01{{6600,360},"Resources/Images/Sprites/Levels/Platforms/platform02.png",0.0f,0.50f,"Resources/Images/Sprites/Levels/Platforms/platform02.svg"}
	  , m_Ladder01{{8090,5.0f},1}
	  , m_pPlayer{player}
{
	InitEnvironement();
	InitializeCoins();

	//Values given to boundaries of level one
	m_Boundaries = {0,0,m_pLevelTwo00->GetWidth(),m_pLevelTwo00->GetHeight()};

	m_BeginPos = Point2f(30, 200);
}

void LevelTwo::InitializeCoins()
{
	m_Coins.push_back(Coin(Point2f{700,340}));
	m_Coins.push_back(Coin(Point2f{750,340}));
	m_Coins.push_back(Coin(Point2f{800,340}));
	m_Coins.push_back(Coin(Point2f{850,340}));


	m_Coins.push_back(Coin(Point2f{1300,335}));
	m_Coins.push_back(Coin(Point2f{1350,335}));
	m_Coins.push_back(Coin(Point2f{1400,335}));
	m_Coins.push_back(Coin(Point2f{1450,335}));

	m_Coins.push_back(Coin(Point2f{1830,335}));
	m_Coins.push_back(Coin(Point2f{2200,335}));


	m_Coins.push_back(Coin(Point2f{4150,120}));
	m_Coins.push_back(Coin(Point2f{4250,170}));
	m_Coins.push_back(Coin(Point2f{4350,220}));
	m_Coins.push_back(Coin(Point2f{4450,270}));
	m_Coins.push_back(Coin(Point2f{4550,320}));
	m_Coins.push_back(Coin(Point2f{4650,370}));
	m_Coins.push_back(Coin(Point2f{4750,420}));
	m_Coins.push_back(Coin(Point2f{4850,470}));

	m_Coins.push_back(Coin(Point2f{8100,50}));
	m_Coins.push_back(Coin(Point2f{8100,150}));
	m_Coins.push_back(Coin(Point2f{8100,250}));
	m_Coins.push_back(Coin(Point2f{8100,350}));
	m_Coins.push_back(Coin(Point2f{8100,450}));
	m_Coins.push_back(Coin(Point2f{8100,550}));
	m_Coins.push_back(Coin(Point2f{8100,650}));
	m_Coins.push_back(Coin(Point2f{8100,750}));
}

void LevelTwo::DrawFront() const
{
	m_pPlayer.lock()->Draw();
	m_pLevelTwo00->Draw(Rectf{0,0,9000,1000});

	DrawTraps();
	m_pFrontMist01->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8,0,9000,1000});// background Mist moving 

	for (const LevelDecorations& decoration : m_DecorationsFront)
	{
		decoration.Draw();
	}


	for (size_t i = 0; i < m_Coins.size(); i++)
	{
		m_Coins[i].Draw();
	}

	m_Platform01.Draw();


	if (m_IsInEndZone)
	{
		m_LoadingScreen.Draw({7720,80,1280,720});
	}
}

void LevelTwo::DrawBack() const
{
	m_pBackMist->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8,0,9000,1200});// background mist moving 01
	m_pTrees01->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 6 ,0,9000,1200});// background trees01 moving 02
	m_pTrees00->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8 ,0,9000,1200});// background trees00 moving 03
	m_pTrees02->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8,0,9000,1200});// background trees02 moving 04	


	m_CircleSaw01.Draw();
	m_CircleSaw02.Draw();
	m_CircleSaw03.Draw();
	m_TrapSpikeFall04.Draw();

	for (const LevelDecorations& decoration : m_DecorationsBack)
	{
		decoration.Draw();
	}

	m_Ladder01.Draw();
}

void LevelTwo::Update(float elapsedSec)
{
	//player pos
	m_PosX = m_pPlayer.lock()->GetShape().left;
	m_PosY = m_pPlayer.lock()->GetShape().bottom;

	m_pPlayer.lock()->SetMovement(true);


	if (m_IsInEndZone)
	{
		m_BeginCount = m_BeginCount + elapsedSec;
	}

	m_TrapSpikeFall01.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall02.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall03.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall04.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw01.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw02.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw03.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSwingBlade02.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSwingBlade03.Update(elapsedSec, m_pPlayer.lock()->GetPosition());

	for (size_t i = 0; i < m_Coins.size(); i++)
	{
		m_Coins[i].Update(elapsedSec);
	}
}

void LevelTwo::DrawTraps() const
{
	m_TrapSpikeFall01.Draw();
	m_TrapSpikeFall02.Draw();
	m_TrapSpikeFall03.Draw();
	m_TrapSwingBlade02.Draw();
	m_TrapSwingBlade03.Draw();
}

void LevelTwo::MouseMoved(const Point2f& mousePos)
{
}

void LevelTwo::MouseClick(const SDL_MouseButtonEvent& e)
{
}

void LevelTwo::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	LevelBase::HandleCollision(actorShape, actorVelocity);
	DeathCollision();
	m_Platform01.HandleCollision(actorShape, actorVelocity);


	// LADDER COLLISION
	if (m_Ladder01.Collision(actorShape))
	{
		m_pPlayer.lock()->SetClimbing(true);
	}
	else
	{
		m_pPlayer.lock()->SetClimbing(false);
	}

	// ending collision, did the player reach the end?
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
		m_LevelManager.SetCurrentLevel(LevelManager::Level::levelThree);
	}


	for (size_t i = 0; i < m_Coins.size(); i++)
	{
		if (m_Coins[i].IsOverlapping(actorShape))
		{
			m_Coins[i].PlayCoinSound();
			m_pPlayer.lock()->AddCoin();
			m_Coins.erase(m_Coins.begin() + i);
		}
	}
}

Rectf LevelTwo::GetBoundaries() const
{
	return m_Boundaries;
}

void LevelTwo::DeathCollision()
{
	if (m_TrapSpikeFall01.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall02.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall03.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall04.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw01.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw02.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw03.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSwingBlade02.BladeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSwingBlade03.BladeCollision(m_pPlayer.lock()->GetShape())
		|| utils::IsOverlapping(m_Pitfall01, m_pPlayer.lock()->GetShape())
		|| utils::IsOverlapping(m_Pitfall02, m_pPlayer.lock()->GetShape())
		|| utils::IsOverlapping(m_Pitfall03, m_pPlayer.lock()->GetShape())
		|| utils::IsOverlapping(m_Pitfall04, m_pPlayer.lock()->GetShape()))
	{
		m_pPlayer.lock()->SetMovement(false);
		m_pPlayer.lock()->SetSecondaryMovement(Character::SecondaryMovement::death);
	}
}

Point2f LevelTwo::GetBeginPos() const
{
	return Point2f(90, 147);
}

void LevelTwo::InitEnvironement()
{
	//Initialize environement
	m_pLevelTwo00 = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Level_Two/leveltwo02.png");

	//back decorations
	m_DecorationsBack.push_back(LevelDecorations{"tree01",{-90.0f,-20.0f},1.0f,1.0f});
	m_DecorationsBack.push_back(LevelDecorations{"tree02",{-490.0f,-20.0f},1.0f,1.0f});

	//front decorations
	m_DecorationsFront.push_back(LevelDecorations{"fence03",{880 ,295},0.75f,1.0f});
	m_DecorationsFront.push_back(LevelDecorations{"fence03",{1600 ,290},0.75f,1.0f});


	m_Pitfall01 = {400,0,300,150};
	m_Pitfall02 = {970,0,1700,150};
	m_Pitfall03 = {5170,0,1000,150};
	m_Pitfall04 = {6460,0,550,150};
}
