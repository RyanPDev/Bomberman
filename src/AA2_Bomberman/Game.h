#pragma once
#include "Types.h"
#include "Renderer.h"
#include "AudioManager.h"
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
	InputData* _input;
	InputManager input;

public:
	Game();
	~Game();

	void Run();
};