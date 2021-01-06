#pragma once
#include <iostream>
#include "Scene.h"
#include "Player.h"
#include "Map.h"

class Gameplay : public Scene
{
private:

public:
	Gameplay();
	~Gameplay();

	//std::vector<Player*> _players;
	void Update(InputData*);
	void Draw();
	void AddPlayer(std::string id, Player::EPlayerType type);
};