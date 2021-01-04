#include "Wall.h"

Wall::Wall(RECT _position): position(_position) {}

Wall::~Wall() {}

void Wall::SetWallValues(int textWidth, int textHeight, int nCol, int nRow)
{
	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;
}