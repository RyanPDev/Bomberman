#include "Player.h"

Player::Player() : position({ 1, 1, 48, 48 }), frame({ 0, 0, 20, 20 }), type(EPlayerType::NONE)
{
	initCol = lastCol = 0;
	initRow = lastRow = 0;
	frameCount = 0;
	score = 0;
	speed = 2;
	speedMultiplier = 3;
}

Player::~Player()
{

}

void Player::Update(InputData* input)
{

}

//void Player::Draw()
//{
//	for (Player* p : _players)
//	{
//		Renderer::GetInstance()->PushSprite(T_PLAYER1, p->GetFrame(), p->GetPosition());
//		Renderer::GetInstance()->PushSprite(T_PLAYER2, p->GetFrame(), p->GetPosition());
//	}
//}

void Player::SetPlayerValues(int textWidth, int textHeight, int nCol, int nRow, EPlayerType _type)
{
	type = _type;

	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;

	switch (_type) {
	case Player::EPlayerType::PL1:
		initCol = 0;
		lastCol = initCol + 2;
		initRow = 0;
		lastRow = initRow + 4;
		frame.x = frame.w * initCol;
		frame.y = frame.h * lastRow;
		score = 0;

		position.x = SCREEN_WIDTH / 2;
		position.y = SCREEN_HEIGHT / 2;
		break;
	case Player::EPlayerType::PL2:
		initCol = 1;
		lastCol = initCol + 2;
		initRow = 0;
		lastRow = initRow + 4;
		frame.x = frame.w * initCol;
		frame.y = frame.h * initRow;
		score = 0;

		position.x = SCREEN_WIDTH / 2;
		position.y = SCREEN_HEIGHT / 2 + 100;
		break;
	default:
		frame.x = 0;
		frame.y = 0;
		break;
	}
}