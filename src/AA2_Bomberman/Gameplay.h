#pragma once
#include <iostream>
#include "Scene.h"
#include "Player.h"
#include "Map.h"

class Gameplay : public Scene
{
private:
	std::vector<Player*> _players;
	Player* p;
	Map map;

public:
	Gameplay();
	~Gameplay();

	void Update(InputManager* input);
	void Draw();
	void AddPlayer(int texWidth, int texHeight, Player::EPlayerType type);
	void InitPlayers();
};