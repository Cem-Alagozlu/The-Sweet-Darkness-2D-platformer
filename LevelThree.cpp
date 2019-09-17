#include "stdafx.h"
#include "LevelThree.h"
#include "SVGParser.h"
#include "Player.h"
#include <sstream>
#include <iostream>
#include "Game.h"
#include "SoundManager.h"


LevelThree::LevelThree(LevelManager& levelmanager, std::shared_ptr<Player> player)
	: LevelBase{levelmanager,"Resources/Images/Sprites/Levels/Level_Three/levelthree.svg"}
	  , m_Ladder01{{1065.0f,250.0f},1}
	  , m_Ladder02{{1065.0f,1025.0f},1}
	  , m_Ladder03{{1065.0f, 1790.0f}, 3}
	  , m_Ladder04{{3350.0f, 240.0f}, 1}
	  , m_Ladder05{{2530.0f,950.0f},2}
	  , m_Ladder06{{2660.0f,1300.0f},3}
	  , m_Ladder07{{2820,1300.0f},3}
	  , m_Ladder08{{2980,1300.0f},3}
	  , m_Ladder09{{3150,1300.0f},3}
	  , m_Ladder10{{3320,1300.0f},2}
	  , m_Ladder11{{3320,1600},3}
	  , m_Ladder12{{7100,300},3}
	  , m_Ladder13{{7250,300},3}//
	  , m_Ladder14{{7400,300},2}//
	  , m_Ladder15{{7570,520},3}//
	  , m_Ladder16{{7730,520},3}//
	  , m_Ladder17{{7900,520},3}//
	  , m_Ladder18{{8050,520},1}//
	  , m_Ladder19{{8424,1170},1}//
	  , m_Ladder20{{7400,300},2}//
	  , m_TrapSwingBlade01{{2650,825},1.0f,0.75f,140}//
	  , m_TrapSwingBlade02{{1700,2400},1.0f,0.40f,140}
	  , m_TrapSwingBlade03{{2650,825},1.0f,0.75f,140}
	  , m_TrapCircleSaw01{{1350,1550},0.15f}
	  , m_TrapCircleSaw02{{1800,1540},0.25f}
	  , m_TrapCircleSaw03{{1950,-250},0.35f}
	  , m_TrapCircleSaw04{{2533,-200},0.25f} // 
	  , m_TrapCircleSaw05{{1000,1520},0.25f} // 
	  , m_TrapCircleSaw06{{5780,-50},0.15f}
	  , m_TrapCircleSaw07{{6250,-70},0.25f}//
	  , m_TrapSpikeFall01{{1700,600},0.0f,1.0f,75.0f,false}//
	  , m_TrapSpikeFall02{{4600,450},0.0f,1.0f,75.0f,false}
	  , m_TrapSpikeFall03{{5520,0},0.0f,3.0f,95.0f,true}
	  , m_TrapSpikeFall04{{5785,750},0.0f,1.0f,75.0f,false}
	  , m_TrapSpikeFall05{{6900,750},0.0f,1.0f,105.0f,false}
	  , m_Pitfall01{480,0,800,120}
	  , m_Pitfall02{3740,0,450,100}
	  , m_Pitfall03{7050,0,1600,150}
	  , m_KillThePlayer{1500,-20,200,800}
	  , m_BigTree01{"Resources/Images/Sprites/Levels/Decoration/kolom01.png"}
	  , m_Lever01{{2600,1918},0.0f,0.50f}
	  , m_Platform01{{520,250},"Resources/Images/Sprites/Levels/Platforms/platform02.png",0.0f,0.50f,"Resources/Images/Sprites/Levels/Platforms/platform02.svg"}
	  , m_pPlayer{player}
{
	//Begin position of player
	m_BeginPos = Point2f(30, 350);

	//Cam positions for cutscene01
	m_CamChangeX = 0;
	m_CamChangeY = 0;

	InitEnvironement();
	InitializeCoins();

	//Values given to boundaries of level one
	m_Boundaries = {0,0,m_pLevelThree00->GetWidth(),m_pLevelThree00->GetHeight()};
}

void LevelThree::InitializeCoins()
{
	m_Coins.push_back(Coin(Point2f{615,300}));

	m_Coins.push_back(Coin(Point2f{1070,900}));
	m_Coins.push_back(Coin(Point2f{1070,990}));
	m_Coins.push_back(Coin(Point2f{1070,1080}));
	m_Coins.push_back(Coin(Point2f{1070,1170}));
	m_Coins.push_back(Coin(Point2f{1070,1260}));
	m_Coins.push_back(Coin(Point2f{1070,1350}));
	m_Coins.push_back(Coin(Point2f{1070,1440}));
	m_Coins.push_back(Coin(Point2f{1070,1530}));
	m_Coins.push_back(Coin(Point2f{1070,1620}));

	m_Coins.push_back(Coin(Point2f{1550,2000}));
	m_Coins.push_back(Coin(Point2f{1840,2000}));
	m_Coins.push_back(Coin(Point2f{1890,2000}));
	m_Coins.push_back(Coin(Point2f{1940,2000}));
	m_Coins.push_back(Coin(Point2f{1990,2000}));
	m_Coins.push_back(Coin(Point2f{2040,2000}));

	m_Coins.push_back(Coin(Point2f{2320,2000}));
	m_Coins.push_back(Coin(Point2f{2370,2000}));
	m_Coins.push_back(Coin(Point2f{2420,2000}));
	m_Coins.push_back(Coin(Point2f{2470,2000}));

	//
	m_Coins.push_back(Coin(Point2f{1950,300}));
	m_Coins.push_back(Coin(Point2f{2000,300}));
	m_Coins.push_back(Coin(Point2f{2050,300}));
	m_Coins.push_back(Coin(Point2f{2100,300}));
	m_Coins.push_back(Coin(Point2f{2150,300}));
	m_Coins.push_back(Coin(Point2f{2200,300}));

	m_Coins.push_back(Coin(Point2f{3100,300}));
	m_Coins.push_back(Coin(Point2f{3150,300}));
	m_Coins.push_back(Coin(Point2f{3200,300}));
	m_Coins.push_back(Coin(Point2f{3250,300}));
	m_Coins.push_back(Coin(Point2f{3300,300}));
	m_Coins.push_back(Coin(Point2f{3350,300}));


	m_Coins.push_back(Coin(Point2f{1500,980}));
	m_Coins.push_back(Coin(Point2f{1550,980}));
	m_Coins.push_back(Coin(Point2f{1600,980}));
	m_Coins.push_back(Coin(Point2f{1650,980}));
	m_Coins.push_back(Coin(Point2f{1700,980}));
	m_Coins.push_back(Coin(Point2f{1750,980}));
	m_Coins.push_back(Coin(Point2f{1800,980}));
	m_Coins.push_back(Coin(Point2f{1850,980}));
	m_Coins.push_back(Coin(Point2f{1900,980}));
	m_Coins.push_back(Coin(Point2f{1950,980}));
	m_Coins.push_back(Coin(Point2f{2000,980}));
	m_Coins.push_back(Coin(Point2f{2050,980}));

	m_Coins.push_back(Coin(Point2f{2540,950}));
	m_Coins.push_back(Coin(Point2f{2540,1050}));
	m_Coins.push_back(Coin(Point2f{2540,1150}));
	m_Coins.push_back(Coin(Point2f{2540,1250}));


	m_Coins.push_back(Coin(Point2f{2700,1350}));
	m_Coins.push_back(Coin(Point2f{2800,1350}));
	m_Coins.push_back(Coin(Point2f{2900,1350}));
	m_Coins.push_back(Coin(Point2f{3000,1350}));
	m_Coins.push_back(Coin(Point2f{3100,1350}));
	m_Coins.push_back(Coin(Point2f{3200,1350}));
	m_Coins.push_back(Coin(Point2f{3300,1350}));


	m_Coins.push_back(Coin(Point2f{4900,60}));
	m_Coins.push_back(Coin(Point2f{5000,160}));
	m_Coins.push_back(Coin(Point2f{5100,260}));
	m_Coins.push_back(Coin(Point2f{5200,360}));
}

void LevelThree::DrawFront() const
{
	// player & level drawn
	m_pPlayer.lock()->Draw();
	m_pLevelThree00->Draw(Rectf{0,0,9000,2400});

	//Draw decorations in map
	for (const LevelDecorations& decoration : m_DecorationsFront)
	{
		decoration.Draw();
	}

	//Draw coins
	for (size_t i = 0; i < m_Coins.size(); i++)
	{
		m_Coins[i].Draw();
	}

	//Loading screen when level ends
	if (m_IsInEndZone)
	{
		m_LoadingScreen.Draw({7720,1448,1280,720});
	}

	//Cutscene sequence 01
	if (m_pPlayer.lock()->GetPosition().x >= 2597.5f
		&& m_pPlayer.lock()->GetPosition().y >= 1900.0f)
	{
		m_pExplaining[m_imgNumber]->Draw({2030,1690});
	}

	//teleport text = drawn
	if (m_IsTeleporting == true)
	{
		m_pExplaining[5]->Draw({3005,1500});
	}
}

void LevelThree::DrawBack() const
{
	m_pBackMist->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8,0,11000,2400});// background mist moving 01
	m_pTrees01->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 6 ,0,11000,2400});// background trees01 moving 02
	m_pTrees00->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8 ,0,11000,2400});// background trees00 moving 03
	m_pTrees02->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8,0,11000,2400});// background trees02 moving 04	

	for (const LevelDecorations& decoration : m_DecorationsBack)
	{
		decoration.Draw();
	}
	DrawTraps();
}

void LevelThree::Update(float elapsedSec)
{
	//Setting if the player can move (true)
	m_pPlayer.lock()->SetMovement(true);

	//player pos
	m_PosX = m_pPlayer.lock()->GetShape().left;
	m_PosY = m_pPlayer.lock()->GetShape().bottom;

	//check if player is in endzone, if true, counter to next level (10)
	if (m_IsInEndZone)
	{
		m_BeginCount = m_BeginCount + elapsedSec;
	}

	//Update for traps 
	m_TrapSwingBlade01.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSwingBlade02.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSwingBlade03.Update(elapsedSec, m_pPlayer.lock()->GetPosition());

	m_TrapCircleSaw01.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapCircleSaw02.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapCircleSaw03.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapCircleSaw04.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapCircleSaw05.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapCircleSaw06.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapCircleSaw07.Update(elapsedSec, m_pPlayer.lock()->GetPosition());

	m_TrapSpikeFall01.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall02.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall03.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall04.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall05.Update(elapsedSec, m_pPlayer.lock()->GetPosition());

	//set movement to false when approach cutscene - lever moment
	if (m_pPlayer.lock()->GetPosition().x >= 2597.5f
		&& m_pPlayer.lock()->GetPosition().y >= 1980.0f
		&& m_imgNumber <= 2)
	{
		m_pPlayer.lock()->SetMovement(false);
	}

	// resets cam & movement for player
	if (m_IsCutScenePassed == false)
	{
		if (m_IsLeverPulled)
		{
			m_pPlayer.lock()->SetMovement(false);
			CutSceneLever();
		}
	}

	//end counter for loading screen
	if (m_IsInEndZone)
	{
		m_BeginCount = m_BeginCount + elapsedSec;
	}

	for (size_t i = 0; i < m_Coins.size(); i++)
	{
		m_Coins[i].Update(elapsedSec);
	}
}

void LevelThree::DrawTraps() const
{
	//not a trap, but ladders to continue 
	m_Ladder01.Draw();
	m_Ladder02.Draw();
	m_Ladder03.Draw();
	m_Ladder04.Draw();
	m_Ladder05.Draw();
	m_Ladder06.Draw();
	m_Ladder07.Draw();
	m_Ladder08.Draw();
	m_Ladder09.Draw();
	m_Ladder10.Draw();
	m_Ladder11.Draw();
	m_Ladder12.Draw();
	m_Ladder13.Draw();
	m_Ladder14.Draw();
	m_Ladder15.Draw();
	m_Ladder16.Draw();
	m_Ladder17.Draw();
	m_Ladder18.Draw();
	m_Ladder19.Draw();
	m_Ladder20.Draw();

	//the circle saws 
	m_TrapCircleSaw01.Draw();
	m_TrapCircleSaw02.Draw();
	m_TrapCircleSaw03.Draw();
	m_TrapCircleSaw04.Draw();
	m_TrapCircleSaw05.Draw();
	m_TrapCircleSaw06.Draw();
	m_TrapCircleSaw07.Draw();

	//blade swinging traps
	m_TrapSwingBlade01.Draw();
	m_TrapSwingBlade02.Draw();
	m_TrapSwingBlade03.Draw();

	//spike falls
	m_TrapSpikeFall01.Draw();
	m_TrapSpikeFall02.Draw();
	m_TrapSpikeFall03.Draw();
	m_TrapSpikeFall04.Draw();
	m_TrapSpikeFall05.Draw();

	//Not a trap, lever + sequence tree + platform01
	m_Lever01.Draw();
	m_BigTree01.Draw({1250,-20.0f - m_Subtractor});
	m_Platform01.Draw();
}

void LevelThree::MouseMoved(const Point2f& mousePos)
{
}

void LevelThree::MouseClick(const SDL_MouseButtonEvent& e)
{
	//text pictures for when you reach the cutscene place
	if (m_imgNumber >= 0 && m_imgNumber <= 2
		&& m_pPlayer.lock()->GetPosition().x >= 2597.5f
		&& m_pPlayer.lock()->GetPosition().y >= 1900.0f)
	{
		++m_imgNumber;
	}

	//teleports player when reached mid section
	if (m_IsTeleporting)
	{
		m_pPlayer.lock()->SetMovement(true);
		m_pPlayer.lock()->SetPosition({4340,95});
		SoundManager::PlaySoundEffect("Teleport", false, true);
		m_pPlayer.lock()->SetLevelBeginPos(Point2f(4340, 95));
		m_IsTeleporting = false;
	}
}

void LevelThree::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	LevelBase::HandleCollision(actorShape, actorVelocity);
	DeathCollision();

	m_Platform01.HandleCollision(actorShape, actorVelocity);
	//checks if player is in the mid section to teleport
	if (utils::IsOverlapping(actorShape, m_Teleport))
	{
		m_pPlayer.lock()->SetMovement(false);
		m_IsTeleporting = true;
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

	// LADDER COLLISION
	if (m_Ladder01.Collision(actorShape)
		|| m_Ladder02.Collision(actorShape)
		|| m_Ladder03.Collision(actorShape)
		|| m_Ladder04.Collision(actorShape)
		|| m_Ladder05.Collision(actorShape)
		|| m_Ladder06.Collision(actorShape)
		|| m_Ladder07.Collision(actorShape)
		|| m_Ladder08.Collision(actorShape)
		|| m_Ladder09.Collision(actorShape)
		|| m_Ladder10.Collision(actorShape)
		|| m_Ladder11.Collision(actorShape)
		|| m_Ladder12.Collision(actorShape)
		|| m_Ladder13.Collision(actorShape)
		|| m_Ladder14.Collision(actorShape)
		|| m_Ladder15.Collision(actorShape)
		|| m_Ladder16.Collision(actorShape)
		|| m_Ladder17.Collision(actorShape)
		|| m_Ladder18.Collision(actorShape)
		|| m_Ladder19.Collision(actorShape)
		|| m_Ladder20.Collision(actorShape))
	{
		m_pPlayer.lock()->SetClimbing(true);
	}
	else
	{
		m_pPlayer.lock()->SetClimbing(false);
	}

	//pulling the lever with "p"
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (m_Lever01.Collision(actorShape))
	{
		if (pStates[SDL_SCANCODE_P])
		{
			m_Lever01.SetLeverPull(true);
			SoundManager::PlaySoundEffect("Lever", false, true);
			m_IsLeverPulled = true;
		}
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
		m_LevelManager.SetCurrentLevel(LevelManager::Level::levelFour);
	}
}

Rectf LevelThree::GetBoundaries() const
{
	return m_Boundaries;
}

void LevelThree::DeathCollision()
{
	if (m_TrapSpikeFall01.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall02.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall03.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall04.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall05.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapCircleSaw01.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapCircleSaw02.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapCircleSaw03.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapCircleSaw04.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapCircleSaw05.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapCircleSaw06.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapCircleSaw07.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSwingBlade01.BladeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSwingBlade02.BladeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSwingBlade03.BladeCollision(m_pPlayer.lock()->GetShape())
		|| utils::IsOverlapping(m_Pitfall01, m_pPlayer.lock()->GetShape())
		|| utils::IsOverlapping(m_Pitfall02, m_pPlayer.lock()->GetShape())
		|| utils::IsOverlapping(m_Pitfall03, m_pPlayer.lock()->GetShape()))
	{
		m_pPlayer.lock()->SetMovement(false);
		m_pPlayer.lock()->SetSecondaryMovement(Character::SecondaryMovement::death);
	}

	if (utils::IsOverlapping(m_KillThePlayer, m_pPlayer.lock()->GetShape()) && m_IsLeverPulled == false)
	{
		m_pPlayer.lock()->SetMovement(false);
		m_pPlayer.lock()->SetSecondaryMovement(Character::SecondaryMovement::death);
	}
}

void LevelThree::CutSceneLever()
{
	Game::m_CamY = m_CamChangeY;
	Game::m_CamX = m_CamChangeX;

	if (m_CamChangeY >= -1500)
	{
		m_CamChangeY -= 5;
	}
	if (m_CamChangeX >= -1100)
	{
		m_CamChangeX -= 2;
	}
	if (m_CamChangeX >= -1100 && m_CamChangeY >= -1500)
	{
		m_BigTreeChangeY -= 5;
	}

	if (m_BigTreeChangeY <= -1500 && m_Subtractor <= 700)
	{
		m_Subtractor += 1.35f;
		if (m_Subtractor >= 690)
		{
			m_CamChangeX = 0;
			m_CamChangeY = 0;
			m_pPlayer.lock()->SetMovement(true);

			if (m_Subtractor >= 695)
			{
				m_IsCutScenePassed = true;
			}
		}
	}
}

void LevelThree::InitEnvironement()
{
	//Initialize environement
	m_pLevelThree00 = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Level_Three/levelthree000.png");

	// Back Decoration
	m_DecorationsBack.push_back(LevelDecorations{"roots1",{1380,750.0f},1.0f,1.0f});
	m_DecorationsBack.push_back(LevelDecorations{"gear1",{2330,1700},0.25f,1.0f});
	m_DecorationsBack.push_back(LevelDecorations{"chain",{50,640},0.75f,1.0f});
	m_DecorationsBack.push_back(LevelDecorations{"chain",{90,640},0.75f,1.0f});
	m_DecorationsBack.push_back(LevelDecorations{"chain",{50,1240},0.75f,1.0f});
	m_DecorationsBack.push_back(LevelDecorations{"chain",{90,1240},0.75f,1.0f});
	m_DecorationsBack.push_back(LevelDecorations{"chain",{50,1840},0.75f,1.0f});
	m_DecorationsBack.push_back(LevelDecorations{"chain",{90,1840},0.75f,1.0f});
	m_DecorationsBack.push_back(LevelDecorations{"ground01",{3200,-100},1,1.0f});

	//front decoration
	m_DecorationsFront.push_back(LevelDecorations{"start",{70 ,790},0.55f,1.0f});
	m_DecorationsFront.push_back(LevelDecorations{"fence03",{250 ,330},0.75f,1.0f});
	m_DecorationsFront.push_back(LevelDecorations{"fence03",{3900 ,1150},0.75f,1.0f});
	m_DecorationsFront.push_back(LevelDecorations{"fence03",{3700 ,1150},0.75f,1.0f});
	m_DecorationsFront.push_back(LevelDecorations{"fence03",{3500 ,1150},0.75f,1.0f});
	for (int idx = 0; idx < m_imgAmount; ++idx)
	{
		std::stringstream str;
		str << "Resources/Images/Sprites/Levels/Level_Three/tut/" << idx + 1 << ".png";
		m_pExplaining.push_back(std::make_unique<Texture>(str.str()));
	}
}
