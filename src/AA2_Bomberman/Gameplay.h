#pragma once
#include <iostream>
#include "Scene.h"
#include "Player.h"
#include "Map.h"
#include <time.h>

class Gameplay : public Scene
{
private:
	////Timer
	//time_t startingTime;
	//time_t updatedTime;
	//time_t timer;
	//struct tm* timerInfo;
	//char timerPtr[80];

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
	void TimerUpdate();
};