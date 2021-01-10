#pragma once
#include "Object.h"
#include "Types.h"

class Wall : public Object
{
private:
	VEC2 coord;
public:
	Wall(RECT);
	~Wall();

	void SetValues(int textWidth, int textHeight, int nCol, int nRow, bool type);

	inline const VEC2* GetCoord()const { return &coord; }

	void SetCoord(VEC2 _coord) { coord = _coord; }
};