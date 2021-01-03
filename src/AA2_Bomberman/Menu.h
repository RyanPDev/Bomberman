#pragma once
#include "Scene.h"

class Menu : public Scene
{
private:

public:
	Menu();
	~Menu();

	void Update(EDirection dir);
	void Draw();
};