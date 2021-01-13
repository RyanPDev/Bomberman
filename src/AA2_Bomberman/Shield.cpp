#include "Shield.h"

Shield::Shield(RECT _position) : Object(_position) {}
Shield::~Shield() {}

void Shield::SetValues(int textWidth, int textHeight, int nCol, int nRow)
{
	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;
	frame.y = frame.h;
	frame.x = frame.w * 2;
}