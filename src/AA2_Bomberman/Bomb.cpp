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
	e = new Explosion(RECT{ bombPos->x, bombPos->y, bombPos->w, bombPos->h });
	e->SetValues(textWidth, textHeight, 4, 7);
}

void Bomb::DrawExplosion()
{
	Renderer::GetInstance()->PushSprite(T_EXPLOSION, e->GetFrame(), e->GetPosition());
}
