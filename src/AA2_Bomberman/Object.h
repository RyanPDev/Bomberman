#pragma once
#include "Types.h"
#include "Renderer.h"

class Object
{
protected:
	RECT position;
	RECT frame;
	int initCol;
	int initRow;
	int lastCol;
	int lastRow;
	float frameCount = 0;

private:
	
public:
	Object(RECT);
	~Object();

	inline const RECT* GetPosition()const { return &position; }
	inline const RECT* GetFrame()const { return &frame; }
};