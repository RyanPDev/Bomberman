#pragma once
#include <iostream>
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "Utils.h"
#include <time.h>

class Gameplay : public Scene
{
private:
	float timeDown;

	//Scores
	std::string scoreStringPl1 = "000", scoreStringPl2 = "000";

	//Lives
	RECT livesFrame;

public:
	Gameplay();
	~Gameplay();

	//std::vector<Player*> _players;
	void Update(InputData*);
	void Draw();
	void AddPlayer(std::string id, Player::EPlayerType type);
	void UpdateHUDText();
};