#include "PowerUp.h"

PowerUp::PowerUp(RECT _position) : Object(_position) {}
PowerUp::~PowerUp() {}

void PowerUp::SetValues(int textWidth, int textHeight, int nCol, int nRow, EPowerUpType _type)
{
	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;
	frame.y = frame.h;
	switch (_type)
	{
	case EPowerUpType::SHIELD:
		type = EPowerUpType::SHIELD;
		frame.x = frame.w * 2;
		break;
	case EPowerUpType::ROLLERS:
		type = EPowerUpType::ROLLERS;
		frame.x = frame.w;
		break;
	default:
		break;
	}
}

PowerUp::EPowerUpType PowerUp::GeneratePowerUp()
{
	return static_cast<EPowerUpType>(rand() % static_cast<int>(EPowerUpType::COUNT));
}

void PowerUp::Draw(EPowerUpType type)
{
	switch (type)
	{
	case PowerUp::EPowerUpType::SHIELD:
		Renderer::GetInstance()->PushSprite(T_SHIELD, &frame, &position);
		break;
	case PowerUp::EPowerUpType::ROLLERS:
		Renderer::GetInstance()->PushSprite(T_ROLLERS, &frame, &position);
		break;
	default:
		break;
	}
}

//void PowerUp::CheckPowerUp(RECT _pos, PowerUp p)
//{
//	int rnd = rand() % 100;
//	if (rnd < 20)
//	{
//		p.SetValues(Renderer::GetInstance()->GetTextureSize(T_ROLLERS).x, Renderer::GetInstance()->GetTextureSize(T_ROLLERS).y, 3, 2, p.GeneratePowerUp());
//		_powerUps.push_back(p);
//	}
//}