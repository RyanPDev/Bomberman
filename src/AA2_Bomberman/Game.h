#pragma once
#include "Types.h"
#include "InputManager.h"
#include "Gameplay.h"
#include "Menu.h"
#include "Ranking.h"
#include <iostream>

class Game
{
private:
	Scene* scene;
	EGameScene gameScene;
	InputManager* inputManager;

public:
	Game();
	~Game();

	void Run();
	void UpdateInput();
};