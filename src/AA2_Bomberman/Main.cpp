#include "Game.h"
#include "Map.h"
#include "Scene.h"
#include "Gameplay.h"
#include "InputManager.h"

int main(int, char* [])
{
	//Player player;
	InputManager input;

	Game game;
	game.Run(input);

	return 0;
}