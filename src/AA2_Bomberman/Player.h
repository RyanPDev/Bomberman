#pragma once
#include "Collisions.h"
#include "Constants.h"
#include "Renderer.h"
#include "Map.h"
#include "InputManager.h"
#include "Bomb.h"
#include "Explosion.h"
#include "Timer.h"

class Player
{
public:
	enum class EPlayerType { NONE = -1, PL1, PL2, COUNT };
	
private:
	Timer timer;
	float currentTime = 0;
	int score;
	int hp;
	float bombTimer = 0;
	bool bombUp;
	bool explosionActive;
	std::vector<Bomb*> _bombs;
	Bomb* b;
	RECT position;
	VEC2 newPosition;
	RECT frame;
	EPlayerType type;
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
	void PlayerCollision();
	VEC2 GetMapPosition(Map*, EPlayerType);
	int GetMapHp(Map*, EPlayerType);
	void DropBomb(Map* map);
	void DrawBomb();
	void DrawExplosion();

	inline const int GetHp()const { return hp; }
	inline const RECT* GetPosition()const { return &position; }
	inline const RECT* GetFrame()const { return &frame; }
	inline const int* GetScore()const { return &score; }
	const bool GetBomb()const { return bombUp; }

};