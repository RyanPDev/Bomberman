#pragma once
#include "Collisions.h"
#include "Object.h"

class Wall
{
private:
	RECT position;
	RECT frame;

public:
	Wall(RECT);
	~Wall();

	void SetWallValues(int textWidth, int textHeight, int nCol, int nRow, bool type);

	inline const RECT* GetPosition()const { return &position; }
	inline const RECT* GetFrame()const { return &frame; }
};