#include "Bomb.h"

Bomb::Bomb(RECT _position) : Object(_position) {}

Bomb::~Bomb() {}

void Bomb::SetValues(int textWidth, int textHeight, int nCol, int nRow)
{
	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;

	frame.y = frame.h;
}

void Bomb::Explode(const RECT* bombPos, int textWidth, int textHeight)
{

}

void Bomb::DrawExplosion()
{
	Renderer::GetInstance()->PushSprite(T_EXPLOSION, e->GetFrame(), e->GetPosition());
}
