#pragma once
#include "Types.h"

class Object
{
protected:
	RECT position;
	RECT frame;

private:
	
public:
	Object(RECT);
	~Object();

	inline const RECT* GetPosition()const { return &position; }
	inline const RECT* GetFrame()const { return &frame; }
};