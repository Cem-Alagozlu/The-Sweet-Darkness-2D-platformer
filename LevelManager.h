#pragma once
#include "Vector2f.h"
#include "Player.h"

class Game;
class LevelOne;
class LevelTwo;
class LevelThree;
class LevelFour;
class LevelBoss;
class LevelEnd;
class Credits;
class LevelBase;

class LevelManager

{
public:
	enum class Level
	{
		noLevel,
		levelOne,
		levelTwo,
		levelThree,
		levelFour,
		levelBoss,
		LevelEnd
	};

	LevelManager(Game& game, std::shared_ptr<Player> player);
	LevelManager(const LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;
	~LevelManager() = default;


	void DrawForeground() const;
	void DrawBackground() const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity) const;
	void Update(float elapsedSec) const;

	void MouseMoved(const Point2f& mousePos) const;
	void MouseClick(const SDL_MouseButtonEvent& e) const;

	static std::shared_ptr<LevelBase> GetCurrentLevel();
	void SetCurrentLevel(Level level);
	Point2f GetLevelBeginPos() const;
private:
	Game& m_Game;

	Level m_CurrentLevel;
	std::shared_ptr<LevelOne> m_pLevelOne;
	std::shared_ptr<LevelTwo> m_pLevelTwo;
	std::shared_ptr<LevelThree> m_pLevelThree;
	std::shared_ptr<LevelFour> m_pLevelFour;
	std::shared_ptr<LevelBoss> m_pLevelBoss;
	std::shared_ptr<LevelEnd> m_pLevelEnd;

	static std::shared_ptr<LevelBase> m_pCurrentLevel;
	std::weak_ptr<Player> m_pPlayer;
};
