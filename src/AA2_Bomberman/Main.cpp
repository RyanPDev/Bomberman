#include "Game.h"
#include "Map.h"
#include "Scene.h"
#include "Gameplay.h"
#include "InputManager.h"

int main(int, char* [])
{/*
	InputManager input;
	InputData _input = input.GetInput();*/

	Game game;
	game.Run();

	return 0;
}