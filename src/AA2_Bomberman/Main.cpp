#include "Game.h"
#include "Map.h"
#include "Scene.h"
#include "Gameplay.h"
#include "InputManager.h"

int main(int, char* [])
{
	//Player player;
	InputData _input;
	InputManager input;

	Game game(_input);
	game.Run(input);

	return 0;
}