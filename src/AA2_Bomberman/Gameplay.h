#pragma once
#include <iostream>
#include "Scene.h"
#include "Player.h"

class Gameplay : public Scene
{
private:
	std::vector<Player*> _players;
	//Player player;

public:
	Gameplay();
	~Gameplay();

	void Update();
	void Draw();
	void InitPlayers();
	void AddPlayers(int texWidth, int texHeight, Player::EPlayerType type);
};