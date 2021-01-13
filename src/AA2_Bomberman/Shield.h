#pragma once
#include "Object.h"

class Shield : public Object
{
private:

public:
	Shield(RECT);
	~Shield();

	void SetValues(int, int, int, int);
};

