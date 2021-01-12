#pragma once
#include "Object.h"
#include "Map.h"
#include "Collisions.h"

class Explosion : public Object
{
public:
	enum class EExplosionDirection { NONE = -1, MID, MID_BOTTOM, BOTTOM, MID_TOP, TOP, MID_LEFT, LEFT, MID_RIGHT, RIGHT, COUNT };

private:
	EExplosionDirection dir = EExplosionDirection::NONE;
	bool visible = false;

public:
	Explosion(RECT);
	~Explosion();

	void SetValues(int, int, int, int, const RECT*, EExplosionDirection);
	void UpdateSprite(VEC2, const float);
	void CheckCollision(bool&, Map*, int&);
	bool GetVisibility()const { return visible; }
};