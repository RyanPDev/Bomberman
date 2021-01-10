#pragma once
#include "Object.h"
#include "Types.h"
#include "Explosion.h"
#include "Renderer.h"

class Bomb : public Object
{
private:
	Explosion* e;
public:
	Bomb(RECT);
	~Bomb();

	void SetValues(int, int, int, int);
	void Explode(const RECT* bombFrame, int textWidth, int textHeight);
	void DrawExplosion();
};