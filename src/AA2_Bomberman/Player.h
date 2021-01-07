#pragma once
#include "Collisions.h"
#include "Constants.h"
#include "Renderer.h"
#include "Map.h"
#include "InputManager.h"

class Player
{
public:
	enum class EPlayerType { NONE = -1, PL1, PL2, COUNT };

private:
	int score;
	int hp;
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
	void Move(InputData*);
	bool UpdatePosition();
	void UpdateSprite();
	void ScreenCollision(VEC2&, InputData*);
	void PlayerWallCollision(Map*);
	void PlayerCollision();
	VEC2 GetMapPosition(Map*, EPlayerType);
	int GetHp(Map*, EPlayerType);

	inline const RECT* GetPosition()const { return &position; }
	inline const RECT* GetFrame()const { return &frame; }
	const int GetScore()const { return score; }
};