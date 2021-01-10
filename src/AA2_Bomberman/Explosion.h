#pragma once
#include "Object.h"
class Explosion : public Object
{
private:

public:
	Explosion(RECT _position);
	~Explosion();

	void SetValues(int, int, int, int);
	void UpdateSprite();
};

