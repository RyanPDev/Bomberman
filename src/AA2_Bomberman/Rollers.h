#pragma once
#include "Object.h"

class Rollers : public Object
{
private:

public:
	Rollers(RECT);
	~Rollers();

	void SetValues(int, int, int, int);
};

