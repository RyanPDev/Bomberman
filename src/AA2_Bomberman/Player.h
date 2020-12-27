#pragma once
#include "Collisions.h"
#include "Constants.h"
#include "Renderer.h"

class Player
{
public:
	enum class EPlayerType { NONE = -1, PL1, PL2, COUNT };

private:
	
	int score;
	RECT position;
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

	void Update(InputData* input);
	void Draw();
	void Init();
	//void AddPlayer(int texWidth, int texHeight, Player::EPlayerType type);
	void SetPlayerValues(int textWidth, int textHeight, int nCol, int nRow, EPlayerType _type);

	inline const RECT* GetPosition()const { return &position; }
	inline const RECT* GetFrame()const { return &frame; }
	const int GetScore()const { return score; }
};