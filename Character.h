#pragma once

class LevelBase;

class Character
{
public:
	enum class PrimaryMovement
	{
		left,
		right,
	};

	enum class SecondaryMovement
	{
		idle,
		walk,
		jump,
		death,
		climbing
	};

	explicit Character(const Rectf& center);
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;
	virtual ~Character() = default;


	virtual void Update(float elapsedSec, std::shared_ptr<LevelBase> level) = 0;
	virtual void Draw() const = 0;

protected:
	PrimaryMovement m_Pmovement = PrimaryMovement::right;
	SecondaryMovement m_Smovement = SecondaryMovement::idle;

	Rectf m_CollisonBox;
	float m_Scale;
	Vector2f m_Velocity;

	void Move(float elapsedSec) const;
};
