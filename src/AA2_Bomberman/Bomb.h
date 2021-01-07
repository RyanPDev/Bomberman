#pragma once
#include "Object.h"
#include "Types.h"

class Bomb : public Object
{
private:

public:
	Bomb(RECT);
	~Bomb();

	void SetValues(int, int, int, int);
};