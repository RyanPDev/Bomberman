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

void Player::Update(Map* map)
{
	Move();
	PlayerWallCollision(map);
	UpdatePosition();
	UpdateSprite();
}

void Player::Draw(std::string id, Player* p)
{
	Renderer::GetInstance()->PushSprite(id, p->GetFrame(), p->GetPosition());
}

void Player::SetPlayerValues(int textWidth, int textHeight, int nCol, int nRow, EPlayerType _type)
{
	type = _type;

	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;

	switch (_type) {
	case Player::EPlayerType::PL1:
		initCol = 1;
		lastCol = initCol + 2;
		initRow = 2;
		lastRow = initRow + 1;
		frame.x = frame.w * initCol;
		frame.y = frame.h * initRow;
		score = 0;

		position.x = 48;
		position.y = 128;
		break;
	case Player::EPlayerType::PL2:
		initCol = 1;
		lastCol = initCol + 2;
		initRow = 2;
		lastRow = initRow + 1;
		frame.x = frame.w * initCol;
		frame.y = frame.h * initRow;
		score = 0;

		position.x = 624;
		position.y = 608;
		break;
	default:
		break;
	}
}

void Player::Move()
{
	dir = EDirection::NONE;
	//VEC2 newPosition = { position.x, position.y };

	switch (type) {
	case Player::EPlayerType::PL1:
		//std::cout << input.IsPressed(EInputKeys::LEFT);
		if (InputManager::GetInstance()->GetInput().IsPressed(EInputKeys::LEFT)) {
			newPosition.x -= speed; dir = EDirection::LEFT;
		}
		else if (InputManager::GetInstance()->GetInput().IsPressed(EInputKeys::RIGHT)) {
			newPosition.x += speed; dir = EDirection::RIGHT;
		}
		else if (InputManager::GetInstance()->GetInput().IsPressed(EInputKeys::UP)) {
			newPosition.y -= speed; dir = EDirection::UP;
		}
		else if (InputManager::GetInstance()->GetInput().IsPressed(EInputKeys::DOWN)) {
			newPosition.y += speed; dir = EDirection::DOWN;
		}
		break;
	case Player::EPlayerType::PL2:
		if (InputManager::GetInstance()->GetInput().IsPressed(EInputKeys::A)) {
			newPosition.x -= speed; dir = EDirection::LEFT;
		}
		else if (InputManager::GetInstance()->GetInput().IsPressed(EInputKeys::D)) {
			newPosition.x += speed; dir = EDirection::RIGHT;
		}
		else if (InputManager::GetInstance()->GetInput().IsPressed(EInputKeys::W)) {
			newPosition.y -= speed; dir = EDirection::UP;
		}
		else if (InputManager::GetInstance()->GetInput().IsPressed(EInputKeys::S)) {
			newPosition.y += speed; dir = EDirection::DOWN;
		}
		break;
	default:
		break;
	}

	//Check player collisions
	ScreenCollision(newPosition);

	//Update position
	//if (newPosition.x != position.x || newPosition.y != position.y) {
	//	position.x = newPosition.x;
	//	position.y = newPosition.y;
	//	return true;
	//}
	//else
	//	frameCount = 0;

	//return false;
}

bool Player::UpdatePosition()
{
	//Update position
	if (newPosition.x != position.x || newPosition.y != position.y) {
		position.x = newPosition.x;
		position.y = newPosition.y;
		return true;
	}
	else
		frameCount = 0;

	return false;
}

void Player::UpdateSprite()
{
	if (dir != EDirection::NONE) frameCount++;

	if (FPS / frameCount <= 9) {
		frameCount = 0;
		frame.x += frame.w;
		if (frame.x >= frame.w * lastCol)
			frame.x = frame.w * (initCol - 1);
	}

	switch (dir) {
	case EDirection::LEFT:
		frame.y = (initRow - 1) * frame.h;
		break;
	case EDirection::RIGHT:
		frame.y = (initRow + 1) * frame.h;
		break;
	case EDirection::UP:
		frame.y = (initRow - 2) * frame.h;
		break;
	case EDirection::DOWN:
		frame.y = (initRow + 0) * frame.h;
		break;
	case EDirection::NONE:
		frame.y = (initRow + 0) * frame.h;
		frame.x = frame.w;
		break;
	default:
		break;
	}
}

void Player::ScreenCollision(VEC2& newPosition)
{
	if (newPosition.x > InputManager::GetInstance()->GetInput().GetScreenSize()->x - (frame.w * 2) + 10 || newPosition.x < frame.w) newPosition.x = position.x;
	if (newPosition.y > InputManager::GetInstance()->GetInput().GetScreenSize()->y - (frame.h * 2) || newPosition.y < InputManager::GetInstance()->GetInput().GetScreenSize()->y - 601) newPosition.y = position.y;
}

void Player::PlayerWallCollision(Map* map)
{
	for (Wall* w : map->walls)
	{
		if (Collisions::ExistCollision(RECT(newPosition.x, newPosition.y, position.w - 10, position.h - 5),
			RECT(w->GetPosition()->x, w->GetPosition()->y, w->GetPosition()->w - 10, w->GetPosition()->h - 25)))
		{
			newPosition.x = position.x;
			newPosition.y = position.y;
		}
	}
}

void Player::PlayerCollision()
{

}