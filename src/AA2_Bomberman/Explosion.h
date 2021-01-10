#pragma once
#include "Object.h"
#include "Map.h"
class Explosion : public Object
{
public:
	enum class EExplosionDirection { NONE = -1, MID, MID_BOTTOM, MID_TOP, MID_LEFT, MID_RIGHT, BOTTOM, TOP, LEFT, RIGHT, COUNT };

private:
	EExplosionDirection dir = EExplosionDirection::NONE;

public:
	Explosion(RECT);
	~Explosion();

	void SetValues(int, int, int, int, const RECT*, EExplosionDirection, Map*);
	void UpdateSprite(const float);
};