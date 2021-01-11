#include "Collisions.h"
#include <SDL.h>

bool Collisions::ExistCollision(VEC2 p1, VEC2 p2, float offset)
{
	return abs((long)(VEC2(p2 - p1)).mod()) < offset;
}

bool Collisions::ExistCollision(VEC2 p1, RECT r1)
{
	return (p1.x > r1.x && p1.x < r1.x + r1.w) && (p1.y > r1.y && p1.y < r1.y + r1.h);
}

//bool Collisions::ExistCollision(RECT r1, RECT r2)
//{
//	return ExistCollision(VEC2(r1.x, r1.y), r2) ||
//		ExistCollision(VEC2(r1.x + r1.w, r1.y), r2) ||
//		ExistCollision(VEC2(r1.x + r1.w, r1.y + r1.h), r2) ||
//		ExistCollision(VEC2(r1.x, r1.y + r1.h), r2);
//}

bool Collisions::ExistCollision(RECT r1, RECT r2)
{
	return (r1.x + r1.w >= r2.x &&
		r2.x + r2.w >= r1.x &&
		r1.y + r1.h >= r2.y &&
		r2.y + r2.h >= r1.y);
}