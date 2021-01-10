#include "Explosion.h"

Explosion::Explosion(RECT _position) : Object(_position) {}

Explosion::~Explosion() {}

void Explosion::SetValues(int textWidth, int textHeight, int nCol, int nRow)
{
	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;

	initCol = 0;
	lastCol = initCol + 3;
	initRow = 0;
	lastRow = initRow;
	frame.x = frame.w * initCol;
	frame.y = frame.h * initRow;

}

void Explosion::UpdateSprite()
{
	frameCount++;
	if (FPS / frameCount <= 9) {
		frameCount = 0;
		frame.x += frame.w;
	}
}
