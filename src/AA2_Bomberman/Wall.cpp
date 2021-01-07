#include "Wall.h"

Wall::Wall(RECT _position) : Object(_position) {}

Wall::~Wall() {}

void Wall::SetValues(int textWidth, int textHeight, int nCol, int nRow, bool type)
{
	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;

	if (type) frame.x = frame.w;
}