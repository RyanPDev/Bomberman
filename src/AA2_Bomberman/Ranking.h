#pragma once
#include "Scene.h"

class Ranking : public Scene
{
private:


public:
	Ranking();
	~Ranking();

	void Update(InputData*);
	void Draw();
};