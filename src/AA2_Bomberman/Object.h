#pragma once
#include "Collisions.h"

class Object
{
protected:
	RECT position;
	RECT frame;

private:
	
public:
	Object();
	~Object();

	inline const RECT* GetPosition()const { return &position; }
	inline const RECT* GetFrame()const { return &frame; }
};