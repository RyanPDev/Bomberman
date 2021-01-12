#pragma once
#include <iostream>
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include "Explosion.h"
#include "Utils.h"
#include <time.h>

class Gameplay : public Scene
{
private:
	float timeDown;
	std::vector<std::string> textureVector;

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