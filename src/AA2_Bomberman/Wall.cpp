#include "Wall.h"

Wall::Wall(RECT _position) : position(_position) {}

Wall::~Wall() {}

void Wall::SetWallValues(int textWidth, int textHeight, int nCol, int nRow, bool type)
{
	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;

	if (type) frame.x = frame.w;
}