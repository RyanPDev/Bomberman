#include "Rollers.h"

Rollers::Rollers(RECT _position) : Object(_position) {}
Rollers::~Rollers() {}

void Rollers::SetValues(int textWidth, int textHeight, int nCol, int nRow)
{
	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;
	frame.y = frame.h;
	frame.x = frame.w;
}