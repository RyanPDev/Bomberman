#pragma once
#include <iostream>
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "Explosion.h"

class Gameplay : public Scene
{
private:
	Map map;
	Player* p;
	float timeDown;
	

	//Scores
	std::string scoreStringPl1 = "000", scoreStringPl2 = "000";

	//Lives
	RECT livesFrame;

public:
	Gameplay();
	~Gameplay();

	void Update(InputData*);
	void Draw();
	void AddPlayer(std::string id, Player::EPlayerType type, VEC2);
	void TakeDamageBehaviour(InputData*);
	void UpdateHUDText();
};