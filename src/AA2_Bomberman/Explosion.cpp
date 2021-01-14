#include "Explosion.h"

Explosion::Explosion(RECT _position) : Object(_position) {}

Explosion::~Explosion() {}

//SETS INITIAL VALUES FOR EACH FRAME OF THE EXPLOSION DEPENDING ON THE DIRECTION
void Explosion::SetValues(int textWidth, int textHeight, int nCol, int nRow, const RECT* bombPos, EExplosionDirection _dir)
{
	dir = _dir;

	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;
	position.w = bombPos->w;
	position.h = bombPos->h;

	switch (dir)
	{
	case EExplosionDirection::MID:
		position.x = bombPos->x;
		position.y = bombPos->y;
		initRow = 0;
		break;
	case EExplosionDirection::MID_BOTTOM:
		position.x = bombPos->x;
		position.y = bombPos->y + FRAME_SIZE;
		frame.y = frame.h * 6;
		initRow = 6;
		break;
	case EExplosionDirection::MID_TOP:
		position.x = bombPos->x;
		position.y = bombPos->y - FRAME_SIZE;
		frame.y = frame.h * 6;
		initRow = 6;
		break;
	case EExplosionDirection::MID_LEFT:
		position.x = bombPos->x - FRAME_SIZE;
		position.y = bombPos->y;
		initRow = 5;
		frame.y = frame.h * 5;
		break;
	case EExplosionDirection::MID_RIGHT:
		position.x = bombPos->x + FRAME_SIZE;
		position.y = bombPos->y;
		frame.y = frame.h * 5;
		initRow = 5;
		break;
	case EExplosionDirection::BOTTOM:
		position.x = bombPos->x;
		position.y = bombPos->y + FRAME_SIZE * 2;
		frame.y = frame.h * 4;
		initRow = 4;
		break;
	case EExplosionDirection::TOP:
		position.x = bombPos->x;
		position.y = bombPos->y - FRAME_SIZE * 2;
		frame.y = frame.h * 3;
		initRow = 3;
		break;
	case EExplosionDirection::LEFT:
		position.x = bombPos->x - FRAME_SIZE * 2;
		position.y = bombPos->y;
		frame.y = frame.h * 1;
		initRow = 1;
		break;
	case EExplosionDirection::RIGHT:
		position.x = bombPos->x + FRAME_SIZE * 2;
		position.y = bombPos->y;
		frame.y = frame.h * 2;
		initRow = 2;
		break;
	default:
		break;
	}

	initCol = 0;
	lastCol = 3;
	lastRow = initRow;
}

//UPDATES EXPLOSION SPRITES THROUGH 1S OF TIME
void Explosion::UpdateSprite(VEC2 mapPos, const float timer)
{
	if ((timer <= 1 && timer >= 0.9) || timer < 0.1)
		frame.x = 0;
	else if ((timer < 0.9 && timer >= 0.8) || (timer < 0.2 && timer >= 0.1))
		frame.x = frame.w;
	else if ((timer < 0.8 && timer >= 0.7) || (timer < 0.3 && timer >= 0.2))
		frame.x = frame.w * 2;
	else if (timer < 0.7 && timer >= 0.3)
		frame.x = frame.w * 3;
}

//CHECKS COLLISIONS BETWEEN EXPLOSIONS AND WALLS AND ACTS ACCORDING TO IT
void Explosion::CheckCollision(bool& stopDirection, Map* map, int& score)
{
	if (!stopDirection)
	{
		visible = true;

		if (position.x < SCREEN_WIDTH - FRAME_SIZE && position.y < SCREEN_HEIGHT - FRAME_SIZE &&
			position.x >= FRAME_SIZE && position.y >= SCREEN_HEIGHT - 576)
		{
			for (int j = 0; j < map->walls.size(); j++)
			{
				if (map->walls[j]->GetPosition()->x == position.x && map->walls[j]->GetPosition()->y == position.y)
				{
					visible = false;
					stopDirection = true;
					if (map->map[ScreenToMap(position, frame).y][ScreenToMap(position, frame).x].destructibleWall)
					{
						map->walls.erase(map->walls.begin() + j);
						score += 15;
						Wall* w = new Wall({ position.x, position.y, FRAME_SIZE, FRAME_SIZE });
						w->SetValues(Renderer::GetInstance()->GetTextureSize(T_DESTROYED_WALL).x, Renderer::GetInstance()->GetTextureSize(T_DESTROYED_WALL).y, 3, 2, Wall::EWallType::DESTROYED_WALL);
						map->walls.push_back(w);
					}
					break;
				}
			}
		}
		else 
			visible = false;
	}
	else 
		visible = false;

	if (dir == EExplosionDirection::LEFT || dir == EExplosionDirection::RIGHT || dir == EExplosionDirection::TOP || dir == EExplosionDirection::BOTTOM)
		stopDirection = false;
}