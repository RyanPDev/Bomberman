#include "Game.h"

int main(int, char* [])
{
	srand(static_cast<unsigned>(time(nullptr)));

	Game game;
	game.Run();

	return 0;
}