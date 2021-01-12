#pragma once
#include "Collisions.h"
#include "Constants.h"
#include "Renderer.h"
#include "Map.h"
#include "InputManager.h"
#include "Bomb.h"
#include "Explosion.h"

class Player
{
public:
	enum class EBombState { NONE = -1, PLANTED, COUNTDOWN, FLICKERING, EXPLOSION, EXPLOSION_COUNTDOWN, COUNT };
	enum class EPlayerType { NONE = -1, PL1, PL2, COUNT };
	std::vector<Explosion> _explosions;
	
private:
	int score;
	int hp;
	float bombTimer = 3.f;
	float explosionTimer = 1.f;
	float immunityTimer = 2.f;
	bool immunity = false;
	std::vector<Bomb*> _bombs;
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
	int speed, speedMultiplier;
	float frameCount;

public:
	Player();
	~Player();

	void Update(InputData*, Map*);
	void Draw(std::string, Player*);
	void SetPlayerValues(int, int, int, int, VEC2, int, EPlayerType);
	void Action(InputData*, Map*);
	bool UpdatePosition();
	void UpdateSprite();
	void ScreenCollision(VEC2&, InputData*);
	void PlayerWallCollision(Map*);
	VEC2 GetMapPosition(Map*, EPlayerType);
	int GetMapHp(Map*, EPlayerType);
	void DropBomb(Map* map);
	void DrawBomb();
	void DrawExplosion(Map*);

	const void SetHp(int _hp) { hp = _hp; }
	inline const int GetHp()const { return hp; }
	inline const RECT* GetPosition()const { return &position; }
	inline const RECT* GetFrame()const { return &frame; }
	inline const int* GetScore()const { return &score; }
	inline const EBombState GetBomb()const { return bombState; }

	inline const bool GetImmunity() const { return immunity; }
	const void SetImmunity(bool _immunity) { immunity = _immunity; }

	const void SetImmunityTimer(float _timer) { immunityTimer = _timer; }
	inline const float GetImmunityTimer()const { return immunityTimer; }
};