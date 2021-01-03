#pragma once
#include "Scene.h"

class Ranking : public Scene
{
private:


public:
	Ranking();
	~Ranking();

	void Update(EDirection dir);
	void Draw();
};