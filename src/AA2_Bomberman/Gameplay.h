#pragma once
#include <iostream>
#include "Scene.h"
#include "Menu.h"
#include "Player.h"
#include "Map.h"
#include "Explosion.h"

class Gameplay : public Scene
{
private:	
	Player* p;
	float timeDown;
	Map map;

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