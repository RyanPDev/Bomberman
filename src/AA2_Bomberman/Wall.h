#pragma once
#include "Object.h"
#include "Types.h"

class Wall : public Object
{
private:

public:
	Wall(RECT);
	~Wall();

	void SetValues(int textWidth, int textHeight, int nCol, int nRow, bool type);
};