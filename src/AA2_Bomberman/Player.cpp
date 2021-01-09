#include "Player.h"

Player::Player() : position({ 1, 1, 48, 48 }), frame({ 0, 0, 20, 20 }), type(EPlayerType::NONE)
{
	initCol = lastCol = 0;
	initRow = lastRow = 0;
	frameCount = 0;
	score = 0;
	speed = 2;
	speedMultiplier = 3;
	hp = 0;
	bombUp = false;
	timer.Start();
}

Player::~Player() {}

void Player::Update(InputData* _input, Map* map)
{
	currentTime = timer.ElapsedSeconds();
	Action(_input, map);
	PlayerWallCollision(map);
	UpdatePosition();
	UpdateSprite();
	if (bombUp)
	{
		DropBomb(map);
	}
}

void Player::Draw(std::string id, Player* p)
{
	Renderer::GetInstance()->PushSprite(id, p->GetFrame(), p->GetPosition());
}

void Player::SetPlayerValues(int textWidth, int textHeight, int nCol, int nRow, VEC2 _position, int _hp, EPlayerType _type)
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
		score = 100;
		hp = _hp;

		position.x = _position.x;
		position.y = _position.y;
		break;
	case Player::EPlayerType::PL2:
		initCol = 1;
		lastCol = initCol + 2;
		initRow = 2;
		lastRow = initRow + 1;
		frame.x = frame.w * initCol;
		frame.y = frame.h * initRow;
		score = 200;
		hp = _hp;

		position.x = _position.x;
		position.y = _position.y;
		break;
	default:
		break;
	}
}

void Player::Action(InputData* _input, Map* map)
{
	dir = EDirection::NONE;

	switch (type) {
	case Player::EPlayerType::PL1:
		if (_input->IsPressed(EInputKeys::LEFT)) {
			newPosition.x -= speed; dir = EDirection::LEFT;
		}
		else if (_input->IsPressed(EInputKeys::RIGHT)) {
			newPosition.x += speed; dir = EDirection::RIGHT;
		}
		else if (_input->IsPressed(EInputKeys::UP)) {
			newPosition.y -= speed; dir = EDirection::UP;
		}
		else if (_input->IsPressed(EInputKeys::DOWN)) {
			newPosition.y += speed; dir = EDirection::DOWN;
		}
		if (_input->IsPressed(EInputKeys::SPACE) && !bombUp) {
			bombUp = true;
		}
		break;
	case Player::EPlayerType::PL2:
		if (_input->IsPressed(EInputKeys::A)) {
			newPosition.x -= speed; dir = EDirection::LEFT;
		}
		else if (_input->IsPressed(EInputKeys::D)) {
			newPosition.x += speed; dir = EDirection::RIGHT;
		}
		else if (_input->IsPressed(EInputKeys::W)) {
			newPosition.y -= speed; dir = EDirection::UP;
		}
		else if (_input->IsPressed(EInputKeys::S)) {
			newPosition.y += speed; dir = EDirection::DOWN;
		}
		if (_input->IsPressed(EInputKeys::RIGHT_CTRL) && !bombUp) {
			bombUp = true;

		}
		break;
	default:
		break;
	}

	//Check player collisions
	ScreenCollision(newPosition, _input);
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
	{
		frameCount = 0;
		dir = EDirection::NONE;
	}

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

void Player::ScreenCollision(VEC2& newPosition, InputData* _input)
{
	if (newPosition.x > _input->GetScreenSize()->x - (frame.w * 2) || newPosition.x < frame.w) newPosition.x = position.x;
	if (newPosition.y > _input->GetScreenSize()->y - (frame.h * 2) || newPosition.y < _input->GetScreenSize()->y - 576) newPosition.y = position.y;
}

void Player::PlayerWallCollision(Map* map)
{
	for (Wall* w : map->walls)
	{
		if (Collisions::ExistCollision(RECT(newPosition.x, newPosition.y, position.w - 10, position.h - 5),
			RECT(w->GetPosition()->x, w->GetPosition()->y, w->GetPosition()->w - 10, w->GetPosition()->h - 5)))
		{
			newPosition.x = position.x;
			newPosition.y = position.y;
		}
	}
}

void Player::PlayerCollision()
{

}

VEC2 Player::GetMapPosition(Map* map, EPlayerType type)
{
	switch (type)
	{
	case EPlayerType::PL1:
		return *map->GetPlayer1Position();
	case EPlayerType::PL2:
		return *map->GetPlayer2Position();
	}
}

int Player::GetMapHp(Map* map, EPlayerType type)
{
	switch (type)
	{
	case EPlayerType::PL1:
		return *map->GetPlayer1Hp();
	case EPlayerType::PL2:
		return *map->GetPlayer2Hp();
	}
}

void Player::DropBomb(Map* map)
{
	if (tmp <= 0)
	{
		b = new Bomb({ position.x, position.y, 48, 48 });
		map->map[position.x / 48 - 1][position.y / 100 - 1].existBomb = true;
		for (int i = 0; i < 11; i++)
			for (int j = 0; j < 13; j++)
			{
				if (map->map[i][j].existBomb)
					std::cout << i << ' ' << j << std::endl;
			}
		
		tmp = currentTime;
		b->SetValues(Renderer::GetInstance()->GetTextureSize(T_BOMB).x, Renderer::GetInstance()->GetTextureSize(T_BOMB).y, 3, 2);
	}

	if (currentTime - tmp >= 3)
	{
		tmp = 0;
		delete b;
		bombUp = false;
	}
}

void Player::DrawBomb()
{
	Renderer::GetInstance()->PushSprite(T_BOMB, b->GetFrame(), b->GetPosition());
}