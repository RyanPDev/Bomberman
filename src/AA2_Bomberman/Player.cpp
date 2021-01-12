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
}

Player::~Player() {}

void Player::Update(InputData* _input, Map* map)
{
	Action(_input, map);
	PlayerWallCollision(map);
	UpdatePosition();
	UpdateSprite();

	if (bombState != EBombState::NONE)
	{
		if (bombState != EBombState::EXPLOSION && bombState != EBombState::EXPLOSION_COUNTDOWN)
			bombTimer -= *_input->GetDeltaTime();
		else if (bombState == EBombState::EXPLOSION_COUNTDOWN)
			explosionTimer -= *_input->GetDeltaTime();

		DropBomb(map);
		if (bombTimer <= 0) bombState = EBombState::EXPLOSION;
		else if (bombTimer <= 1) bombState = EBombState::FLICKERING;
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
		score = 0;
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
		score = 0;
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
	case Player::EPlayerType::PL2:
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
		if (_input->IsPressed(EInputKeys::RIGHT_CTRL)) {
			if (bombState == EBombState::NONE) bombState = EBombState::PLANTED;
		}
		break;
	case Player::EPlayerType::PL1:
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
		if (_input->IsPressed(EInputKeys::SPACE)) {
			if (bombState == EBombState::NONE) bombState = EBombState::PLANTED;
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
			RECT(w->GetPosition()->x, w->GetPosition()->y, w->GetPosition()->w - 10, w->GetPosition()->h - 10)))
		{
			newPosition.x = position.x;
			newPosition.y = position.y;
		}
	}
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
	switch (bombState)
	{
	case EBombState::PLANTED:
	{
		bombMapPos = { (position.x + frame.w / 2) / FRAME_SIZE - 1, ((position.y + frame.h / 2) - (80 + FRAME_SIZE)) / FRAME_SIZE };
		b = new Bomb({ bombMapPos.x * 48 + 48, bombMapPos.y * 48 + 128, 48, 48 });
		map->map[bombMapPos.x][bombMapPos.y].existBomb = true;

		b->SetValues(Renderer::GetInstance()->GetTextureSize(T_BOMB).x, Renderer::GetInstance()->GetTextureSize(T_BOMB).y, 3, 2);
		bombState = EBombState::COUNTDOWN;
		break;
	}
	case EBombState::EXPLOSION:
		bombTimer = 3;
		bombState = EBombState::EXPLOSION_COUNTDOWN;
		//Create Explosion
		{
			bool isValid, stopDirection = false;

			for (int i = 0; i < static_cast<int>(Explosion::EExplosionDirection::COUNT); i++)
			{
				Explosion e(RECT{ 0,0,0,0 });
				Explosion::EExplosionDirection dir = static_cast<Explosion::EExplosionDirection>(i);

				e.SetValues(Renderer::GetInstance()->GetTextureSize(T_EXPLOSION).x, Renderer::GetInstance()->GetTextureSize(T_EXPLOSION).y, 4, 7, b->GetPosition(), dir);
				e.CheckCollision(stopDirection, map, score);
				_explosions.push_back(std::move(e));
			}
		}
		delete b;
		break;
	case EBombState::EXPLOSION_COUNTDOWN:
		//Explosion animation 1s
		for (int i = 0; i < _explosions.size(); i++)
		{
			_explosions[i].UpdateSprite(bombMapPos, explosionTimer);
			//if (Collisions::ExistCollision(*_explosions[i].GetPosition(), position))
			//{
			//	//-->TAKE DAMAGE()
			//}
		}

		//Explosion ends
		if (explosionTimer <= 0)
		{
			_explosions.clear();
			bombState = EBombState::NONE;
			explosionTimer = 1;
		}
		break;
	default:
		break;
	}
}

void Player::DrawBomb()
{
	if (bombState == EBombState::COUNTDOWN)	Renderer::GetInstance()->PushSprite(T_BOMB, b->GetFrame(), b->GetPosition());

	else if (bombState == EBombState::FLICKERING)
	{
		if (bombTimer <= 0.875f && bombTimer >= 0.75f || bombTimer <= 0.625f && bombTimer >= 0.5f || bombTimer <= 0.375f && bombTimer >= 0.25f)
		{
			Renderer::GetInstance()->PushSprite(T_BOMB, b->GetFrame(), b->GetPosition());
		}
	}
}

void Player::DrawExplosion(Map* map)
{
	if (bombState == EBombState::EXPLOSION_COUNTDOWN)
	{
		for (int i = 0; i < _explosions.size(); i++)
		{
			if (_explosions[i].GetVisibility())
				Renderer::GetInstance()->PushSprite(T_EXPLOSION, _explosions[i].GetFrame(), _explosions[i].GetPosition());
		}
	}
}