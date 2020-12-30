#pragma once
#include "Scene.h"

class Menu : public Scene
{
private:
	std::string texturePlay;
	std::string textureExit;
	std::string textureSound;

public:
	Menu();
	~Menu();

	void Update(InputManager input);
	void Draw();
};