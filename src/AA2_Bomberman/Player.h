#pragma once
#include "Collisions.h"
#include "Constants.h"
#include "Renderer.h"
#include "Map.h"
#include "InputManager.h"
#include "Bomb.h"
#include "Explosion.h"
#include "PowerUp.h"

class Player
{
public:
	enum class EBombState { NONE = -1, PLANTED, COUNTDOWN, FLICKERING, EXPLOSION, EXPLOSION_COUNTDOWN, COUNT };
	enum class EPlayerType { NONE = -1, PL1, PL2, COUNT };
	std::vector<Explosion> _explosions;
	
private:
	int score;
	int hp;
	VEC2 initialPos;
	float bombTimer;
	float explosionTimer;
	float immunityTimer;
	float deathTimer;
	float powerUpTimer;
	bool deathImmunity;
	bool shieldImmunity;
	bool speedBoost;
	const float SPEED_MULTIPLIER = 3.6f;
	const float BASE_SPEED = 2;
	bool dead;
	
	Bomb* b;
	VEC2 bombMapPos;
	RECT position;
	VEC2 newPosition;
	RECT frame;
	EPlayerType type;
	EBombState bombState = EBombState::NONE;
	EDirection dir = EDirection::NONE;

	int initCol, lastCol;
	int initRow, lastRow;
	int speed;
	float speedMultiplier;
	float frameCount;

public:
	Player();
	~Player();

	void Update(InputData*, Map*, std::vector<PowerUp>&);
	void Draw(std::string, Player*);
	void DrawHp(std::string, RECT*, EPlayerType);
	void SetPlayerValues(int, int, int, int, int, EPlayerType, VEC2);
	void Action(InputData*, Map*);
	bool UpdatePosition();
	void UpdateSprite();
	void ScreenCollision(VEC2&, InputData*);
	void PlayerWallCollision(Map*);
	void PlayerPowerUpCollision(std::vector<PowerUp>& _powerUp);
	int GetMapHp(Map*, EPlayerType);
	void BombState(Map*, std::vector<PowerUp>&);
	void DrawBomb();
	void DrawExplosion(Map*);
	void DeathManagement(InputData*);
	void PowerUpManagement(InputData*);
	void BombManager(InputData*);

	inline const RECT* GetFrame()const { return &frame; }
	inline const EBombState GetBomb()const { return bombState; }

	const void SetHp(int _hp) { hp -= _hp; }
	inline const int GetHp()const { return hp; }

	inline const VEC2 GetInitialPosition() const { return initialPos; }
	inline const RECT* GetPosition()const { return &position; }
	const void SetPosition(VEC2 _pos) { newPosition.x = _pos.x; newPosition.y = _pos.y; }

	inline const int* GetScore()const { return &score; }
	const void SetScore(int _score) { score += _score; }

	inline const bool GetDeathImmunity() const { return deathImmunity; }
	const void SetDeathImmunity(bool _immunity) { deathImmunity = _immunity; }

	const void SetImmunityTimer(float _timer) { immunityTimer = _timer; }
	inline const float GetImmunityTimer()const { return immunityTimer; }

	const void SetDeathTimer(float _timer) { deathTimer = _timer; }
	inline const float GetDeathTimer()const { return deathTimer; }

	const void SetDeath(bool _death) { dead = _death; }
	inline const bool GetDeath() { return dead; }

	inline const bool GetShieldImmunity() { return shieldImmunity; }
};