#include "stdafx.h"
#include "LevelFour.h"
#include "Game.h"

LevelFour::LevelFour(LevelManager& levelmanager, std::shared_ptr<Player> player)
	: LevelBase{levelmanager,"Resources/Images/Sprites/Levels/Level_Four/levelfour.svg"}
	  , m_pPlayer{player}
	  , m_Ladder01{{495,1575},2}
	  , m_Ladder02{{900,1155},2}
	  , m_Ladder03{{1180,760},2}
	  , m_Ladder04{{1020,760},3}
	  , m_Ladder05{{840,760},3}
	  , m_Ladder06{{660,760},3}
	  , m_Ladder07{{480,760},3}
	  , m_Ladder08{{300,760},3}
	  , m_Ladder09{{140,760},3}
	  , m_Ladder10{{-10,120},1}
	  , m_Ladder11{{1450,40},2}
	  , m_Ladder12{{8300,650},1}
	  , m_Ladder13{{7400,0},1}
	  , m_Ladder14{{8577,440},1}
	  , m_PlatformMoving01{{1700,-50},{1700,1200},0.0f,1.0f,1}
	  , m_PlatformMoving02{{6200,1000},{7800,1000},0.0f,1.0f ,2}
	  , m_PlatformMoving03{{7450,-40},{8100,-40},0.0f,1.0f,2}
	  , m_PlatformMoving04{{7500,500},{7800,500},0.0f,1.0f ,2}
	  , m_PlatformMoving05{{2200,1900},{3400,1900},0.0f,0.5f ,2}
	  , m_PlatformMoving06{{3800,1900},{4300,1900},0.0f,0.5f ,2}
	  , m_PlatformMoving07{{4500,1900},{4800,1900},0.0f,0.5f ,2}
	  , m_PlatformMoving08{{5050,1900},{5050,2000},0.0f,0.5f ,1}
	  , m_Platform01{{2200,1300},"Resources/Images/Sprites/Levels/Platforms/platform02.png",0.0f,1.0f,"Resources/Images/Sprites/Levels/Platforms/platform02.svg"}
	  , m_Platform02{{3000,1300},"Resources/Images/Sprites/Levels/Platforms/platform02.png",0.0f,1.0f,"Resources/Images/Sprites/Levels/Platforms/platform02.svg"}
	  , m_Platform03{{3800,1300},"Resources/Images/Sprites/Levels/Platforms/platform02.png",0.0f,1.0f,"Resources/Images/Sprites/Levels/Platforms/platform02.svg"}
	  , m_Platform04{{4600,1300},"Resources/Images/Sprites/Levels/Platforms/platform02.png",0.0f,1.0f,"Resources/Images/Sprites/Levels/Platforms/platform02.svg"}
	  , m_Platform05{{5400,1300},"Resources/Images/Sprites/Levels/Platforms/platform4.png",0.0f,1.0f,"Resources/Images/Sprites/Levels/Platforms/platform4.svg"}
	  , m_Platform06{{3500,2000},"Resources/Images/Sprites/Levels/Platforms/platform02.png",0.0f,0.50f,"Resources/Images/Sprites/Levels/Platforms/platform02.svg"}
	  , m_CircleSaw01{{320,1130},0.15f}
	  , m_CircleSaw02{{10,680},0.10f}
	  , m_CircleSaw03{{250,680},0.10f}
	  , m_CircleSaw04{{2120,940},0.10f}
	  , m_CircleSaw05{{3000,940},0.10f}
	  , m_CircleSaw06{{3700,940},0.10f}
	  , m_CircleSaw07{{4500,940},0.10f}
	  , m_CircleSaw08{{7050,1300},0.5f}
	  , m_CircleSaw09{{5200,1550},0.25f}
	  , m_CircleSaw10{{6000,1500},0.25f}
	  , m_CircleSaw11{{4500,940},0.10f}
	  , m_TrapSpikeFall01{{1300,400},0.0f,1.0f,80,false}
	  , m_TrapSpikeFall02{{380,420},0.0f,1.0f,90,false}
	  , m_TrapBladeSwing01{{5842,1900},1.0f,0.65f,110.0f}
	  , m_Pitfall01{1645,-4,6584,40}
	  , m_Pitfall02{2370,1910,2890,40}
	  , m_BigTree01{"Resources/Images/Sprites/Levels/Decoration/kolom01.png"}
	  , m_LeverTexture{"Resources/Images/Sprites/Levels/Level_Four/1.png"}
	  , m_Lever01{{8800,40},0.0f,0.50f}
	  , m_KillThePlayer{1340,2000,200,800}
{
	//Begin position of player 40 2000
	m_BeginPos = Point2f(40, 2000);

	InitEnvironement();
	InitializeCoins();

	//Values given to boundaries of level one
	m_Boundaries = {0,0,m_pLevelFour00->GetWidth(),m_pLevelFour00->GetHeight()};
}

void LevelFour::InitializeCoins()
{
	m_Coins.push_back(Coin(Point2f{20,1580}));
	m_Coins.push_back(Coin(Point2f{100,1580}));
	m_Coins.push_back(Coin(Point2f{180,1580}));
	m_Coins.push_back(Coin(Point2f{260,1580}));
	m_Coins.push_back(Coin(Point2f{340,1580}));
	m_Coins.push_back(Coin(Point2f{420,1580}));

	m_Coins.push_back(Coin(Point2f{300,1130}));
	m_Coins.push_back(Coin(Point2f{460,1130}));
	m_Coins.push_back(Coin(Point2f{600,1130}));
	m_Coins.push_back(Coin(Point2f{800,1130}));


	m_Coins.push_back(Coin(Point2f{8550,130}));
	m_Coins.push_back(Coin(Point2f{8600,130}));
	m_Coins.push_back(Coin(Point2f{8650,130}));

	m_Coins.push_back(Coin(Point2f{7600,160}));
	m_Coins.push_back(Coin(Point2f{7650,160}));
	m_Coins.push_back(Coin(Point2f{7700,160}));
	m_Coins.push_back(Coin(Point2f{7750,160}));
	m_Coins.push_back(Coin(Point2f{7800,160}));
	m_Coins.push_back(Coin(Point2f{7850,160}));
	m_Coins.push_back(Coin(Point2f{7900,160}));
	m_Coins.push_back(Coin(Point2f{7950,160}));
	m_Coins.push_back(Coin(Point2f{8000,160}));
	m_Coins.push_back(Coin(Point2f{8050,160}));
	m_Coins.push_back(Coin(Point2f{8100,160}));
	m_Coins.push_back(Coin(Point2f{8150,160}));
	m_Coins.push_back(Coin(Point2f{8200,160}));


	m_Coins.push_back(Coin(Point2f{7600,700}));
	m_Coins.push_back(Coin(Point2f{7650,700}));
	m_Coins.push_back(Coin(Point2f{7700,700}));
	m_Coins.push_back(Coin(Point2f{7750,700}));
	m_Coins.push_back(Coin(Point2f{7800,700}));
	m_Coins.push_back(Coin(Point2f{7850,700}));
	m_Coins.push_back(Coin(Point2f{7900,700}));
	m_Coins.push_back(Coin(Point2f{7950,700}));
	m_Coins.push_back(Coin(Point2f{8000,700}));
	m_Coins.push_back(Coin(Point2f{8050,700}));
	m_Coins.push_back(Coin(Point2f{8100,700}));
	m_Coins.push_back(Coin(Point2f{8150,700}));
	m_Coins.push_back(Coin(Point2f{8200,700}));


	m_Coins.push_back(Coin(Point2f{5080,1400}));
	m_Coins.push_back(Coin(Point2f{4770,1400}));
	m_Coins.push_back(Coin(Point2f{4200,1400}));
	m_Coins.push_back(Coin(Point2f{3900,1400}));
	m_Coins.push_back(Coin(Point2f{3490,1400}));
	m_Coins.push_back(Coin(Point2f{3280,1400}));
	m_Coins.push_back(Coin(Point2f{3100,1400}));
	m_Coins.push_back(Coin(Point2f{2700,1400}));
	m_Coins.push_back(Coin(Point2f{2650,1400}));
	m_Coins.push_back(Coin(Point2f{2600,1400}));
	m_Coins.push_back(Coin(Point2f{2550,1400}));
	m_Coins.push_back(Coin(Point2f{2500,1400}));
	m_Coins.push_back(Coin(Point2f{2450,1400}));
	m_Coins.push_back(Coin(Point2f{2400,1400}));
	m_Coins.push_back(Coin(Point2f{2350,1400}));
	m_Coins.push_back(Coin(Point2f{2300,1400}));

	m_Coins.push_back(Coin(Point2f{2400,2050}));
	m_Coins.push_back(Coin(Point2f{2500,2050}));
	m_Coins.push_back(Coin(Point2f{2600,2050}));
	m_Coins.push_back(Coin(Point2f{2700,2050}));
	m_Coins.push_back(Coin(Point2f{2800,2050}));
	m_Coins.push_back(Coin(Point2f{2900,2050}));
	m_Coins.push_back(Coin(Point2f{3000,2050}));
	m_Coins.push_back(Coin(Point2f{3100,2050}));
	m_Coins.push_back(Coin(Point2f{3200,2050}));
	m_Coins.push_back(Coin(Point2f{3300,2050}));
	m_Coins.push_back(Coin(Point2f{3400,2050}));
}

void LevelFour::DrawFront() const
{
	// player & level drawn
	m_pPlayer.lock()->Draw();
	m_pLevelFour00->Draw(Rectf{0,0,9000,2400});

	if (m_IsLeverPulled == false)
	{
		m_BigTree01.Draw({1165,1875});
	}


	for (size_t i = 0; i < m_Coins.size(); i++)
	{
		m_Coins[i].Draw();
	}


	if (m_pPlayer.lock()->GetPosition().x >= 8750 && m_IsLeverPulled)
	{
		m_LeverTexture.Draw(Rectf{7720,0,1280,720});
	}

	//Loading screen when level ends
	if (m_IsInEndZone)
	{
		m_LoadingScreen.Draw({7720,130,1280,720});
	}
}

void LevelFour::DrawBack() const
{
	//moving backgrounds
	m_pBackMist->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8,0,11000,2400});// background mist moving 01
	m_pTrees01->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 6 ,0,11000,2400});// background trees01 moving 02
	m_pTrees00->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8 ,0,11000,2400});// background trees00 moving 03
	m_pTrees02->Draw({-1000 + m_pPlayer.lock()->GetShape().left / 8,0,11000,2400});// background trees02 moving 04	

	//moving platforms
	m_PlatformMoving01.Draw();
	m_PlatformMoving02.Draw();
	m_PlatformMoving03.Draw();
	m_PlatformMoving04.Draw();
	m_PlatformMoving05.Draw();
	m_PlatformMoving06.Draw();
	m_PlatformMoving07.Draw();
	m_PlatformMoving08.Draw();

	//static platforms
	m_Platform01.Draw();
	m_Platform02.Draw();
	m_Platform03.Draw();
	m_Platform04.Draw();
	m_Platform05.Draw();
	m_Platform06.Draw();

	DrawTraps();
}

void LevelFour::Update(float elapsedSec)
{
	//Setting if the player can move (true)
	m_pPlayer.lock()->SetMovement(true);

	//updates the position from players with platforms (x&y)
	m_PlatformMoving01.Update(elapsedSec);
	m_PlatformMoving02.Update(elapsedSec);
	m_PlatformMoving03.Update(elapsedSec);
	m_PlatformMoving04.Update(elapsedSec);
	m_PlatformMoving05.Update(elapsedSec);
	m_PlatformMoving06.Update(elapsedSec);
	m_PlatformMoving07.Update(elapsedSec);
	m_PlatformMoving08.Update(elapsedSec);

	//updates TRAP CircleSaw
	m_CircleSaw01.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw02.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw03.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw04.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw05.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw06.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw07.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw08.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw09.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw10.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_CircleSaw11.Update(elapsedSec, m_pPlayer.lock()->GetPosition());

	//updates TRAP spike fall down
	m_TrapSpikeFall01.Update(elapsedSec, m_pPlayer.lock()->GetPosition());
	m_TrapSpikeFall02.Update(elapsedSec, m_pPlayer.lock()->GetPosition());

	//updates TRAP swing blade
	m_TrapBladeSwing01.Update(elapsedSec, m_pPlayer.lock()->GetPosition());

	//player pos
	m_PosX = m_pPlayer.lock()->GetShape().left;
	m_PosY = m_pPlayer.lock()->GetShape().bottom;

	for (size_t i = 0; i < m_Coins.size(); i++)
	{
		m_Coins[i].Update(elapsedSec);
	}

	//check if player is in endzone, if true, counter to next level (10)
	if (m_IsInEndZone)
	{
		m_BeginCount = m_BeginCount + elapsedSec;
	}
}

void LevelFour::DrawTraps() const
{
	//NOT traps but stairs for the player
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

	//Circle SAW
	m_CircleSaw01.Draw();
	m_CircleSaw02.Draw();
	m_CircleSaw03.Draw();
	m_CircleSaw04.Draw();
	m_CircleSaw05.Draw();
	m_CircleSaw06.Draw();
	m_CircleSaw07.Draw();
	m_CircleSaw08.Draw();
	m_CircleSaw09.Draw();
	m_CircleSaw10.Draw();
	m_CircleSaw11.Draw();

	//Trap Spike Fall down
	m_TrapSpikeFall01.Draw();
	m_TrapSpikeFall02.Draw();

	//Trap Swing Blade
	m_TrapBladeSwing01.Draw();

	m_Lever01.Draw();
}

void LevelFour::MouseMoved(const Point2f& mousePos)
{
}

void LevelFour::MouseClick(const SDL_MouseButtonEvent& e)
{
}

void LevelFour::HandleCollision(Rectf& actorShape, Vector2f& actorVelocity)
{
	//Level collision (from svg file) origin : base class
	LevelBase::HandleCollision(actorShape, actorVelocity);

	DeathCollision();

	//collision between moving platform and player
	m_PlatformMoving01.HandleCollision(actorShape, actorVelocity);
	m_PlatformMoving02.HandleCollision(actorShape, actorVelocity);
	m_PlatformMoving03.HandleCollision(actorShape, actorVelocity);
	m_PlatformMoving04.HandleCollision(actorShape, actorVelocity);
	m_PlatformMoving05.HandleCollision(actorShape, actorVelocity);
	m_PlatformMoving06.HandleCollision(actorShape, actorVelocity);
	m_PlatformMoving07.HandleCollision(actorShape, actorVelocity);
	m_PlatformMoving08.HandleCollision(actorShape, actorVelocity);

	//collision between static platform and player
	m_Platform01.HandleCollision(actorShape, actorVelocity);
	m_Platform02.HandleCollision(actorShape, actorVelocity);
	m_Platform03.HandleCollision(actorShape, actorVelocity);
	m_Platform04.HandleCollision(actorShape, actorVelocity);
	m_Platform05.HandleCollision(actorShape, actorVelocity);
	m_Platform06.HandleCollision(actorShape, actorVelocity);

	//if the player is on the platform, his positions will be updated!
#pragma region platform_move_changes
	if (m_PlatformMoving01.PlatformCollision(actorShape))
	{
		m_PlatformMoving01.PlatformPlayerChange(actorShape);
	}

	if (m_PlatformMoving02.PlatformCollision(actorShape))
	{
		m_PlatformMoving02.PlatformPlayerChange(actorShape);
	}

	if (m_PlatformMoving03.PlatformCollision(actorShape))
	{
		m_PlatformMoving03.PlatformPlayerChange(actorShape);
	}

	if (m_PlatformMoving04.PlatformCollision(actorShape))
	{
		m_PlatformMoving04.PlatformPlayerChange(actorShape);
	}

	if (m_PlatformMoving05.PlatformCollision(actorShape))
	{
		m_PlatformMoving05.PlatformPlayerChange(actorShape);
	}

	if (m_PlatformMoving06.PlatformCollision(actorShape))
	{
		m_PlatformMoving06.PlatformPlayerChange(actorShape);
	}

	if (m_PlatformMoving07.PlatformCollision(actorShape))
	{
		m_PlatformMoving07.PlatformPlayerChange(actorShape);
	}

	if (m_PlatformMoving08.PlatformCollision(actorShape))
	{
		m_PlatformMoving08.PlatformPlayerChange(actorShape);
	}
#pragma endregion

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
		|| m_Ladder14.Collision(actorShape))
	{
		m_pPlayer.lock()->SetClimbing(true);
	}
	else
	{
		m_pPlayer.lock()->SetClimbing(false);
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


	//pulling the lever with "p"
	const Uint8* pStates = SDL_GetKeyboardState(nullptr);
	if (m_Lever01.Collision(actorShape))
	{
		if (pStates[SDL_SCANCODE_P])
		{
			m_Lever01.SetLeverPull(true);
			m_IsLeverPulled = true;
			SoundManager::PlaySoundEffect("Lever", false, true);
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
		m_LevelManager.SetCurrentLevel(LevelManager::Level::levelBoss);
	}
}

Rectf LevelFour::GetBoundaries() const
{
	return m_Boundaries;
}

void LevelFour::DeathCollision()
{
	if (m_TrapSpikeFall01.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapSpikeFall02.SpikeCollision(m_pPlayer.lock()->GetShape())
		|| m_TrapBladeSwing01.BladeCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw01.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw02.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw03.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw04.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw05.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw06.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw07.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw08.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw09.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw10.CircleCollision(m_pPlayer.lock()->GetShape())
		|| m_CircleSaw11.CircleCollision(m_pPlayer.lock()->GetShape())
		|| utils::IsOverlapping(m_Pitfall01, m_pPlayer.lock()->GetShape())
		|| utils::IsOverlapping(m_Pitfall02, m_pPlayer.lock()->GetShape()))

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


void LevelFour::InitEnvironement()
{
	m_pLevelFour00 = std::make_unique<Texture>("Resources/Images/Sprites/Levels/Level_Four/levelfour00.png");
}
