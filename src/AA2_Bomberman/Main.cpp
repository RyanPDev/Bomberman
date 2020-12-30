#include "Game.h"
#include "Map.h"
#include "Scene.h"
#include "Gameplay.h"
#include "InputManager.h"

int main(int, char* [])
{
	//Map map;
	InputManager input;

	Game game(input);
	game.Run(input);

	return 0;
}