#pragma once
#include "Scene.h"
#include <iostream>

class Gameplay : public Scene
{
private:
	int a = 0;

public:
	Gameplay();
	~Gameplay();

	void Update();
	void Draw();	
};