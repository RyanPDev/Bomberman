#pragma once
#include <iostream>
#include "Scene.h"
#include "Player.h"
#include "Map.h"

class Gameplay : public Scene
{
private:
	Player* p;
	Map map;

public:
	Gameplay();
	~Gameplay();

	std::vector<Player*> _players;
	void Update();
	void Draw();
	void AddPlayer(int texWidth, int texHeight, Player::EPlayerType type);
	void InitPlayers();
};