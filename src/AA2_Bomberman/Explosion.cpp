#include "Explosion.h"

Explosion::Explosion(RECT _position) : Object(_position) {}

Explosion::~Explosion() {}

void Explosion::SetValues(int textWidth, int textHeight, int nCol, int nRow, const RECT* bombPos, EExplosionDirection _dir, Map* map, bool& stopDirection, int& score)
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
					if (map->map[((position.y + frame.h / 2) - (80 + FRAME_SIZE)) / FRAME_SIZE][(position.x + frame.w / 2) / FRAME_SIZE - 1].destructibleWall)
					{
						map->walls.erase(map->walls.begin() + j);
						score += 15;
					}
					break;
				}
			}
		}

		else
		{
			visible = false;
		}
	}
	else
		visible = false;

	if (dir == EExplosionDirection::LEFT || dir == EExplosionDirection::RIGHT || dir == EExplosionDirection::TOP || dir == EExplosionDirection::BOTTOM)
		stopDirection = false;
}

void Explosion::UpdateSprite(VEC2 mapPos, const float timer, Map* map)
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

void Explosion::CheckCollision(VEC2 mapPos, Map* map, int& score)
{
	//LES COLISIONS NECESSITEN UN REFER PER LA FASE 3. A MES NO FUNCIONA BÉ. PLUS ELS PLAYERS NO PERDEN VIDA

	if (map->map[mapPos.y][mapPos.x + 2].existWall && !map->map[mapPos.y][mapPos.x + 1].existWall)
	{
		if (map->map[mapPos.y][mapPos.x + 2].destructibleWall)
		{
			for (int i = 0; i < map->walls.size(); i++)
			{
				if (map->walls[i]->GetCoord()->x == mapPos.x + 2 && map->walls[i]->GetCoord()->y == mapPos.y)
				{
					map->walls.erase(map->walls.begin() + i);
					map->map[mapPos.y][mapPos.x + 2].existWall = false;
					score += 15;
				}
			}
		}
	}

	if (map->map[mapPos.y][mapPos.x - 2].existWall)
	{
		if (dir == EExplosionDirection::MID_LEFT || dir == EExplosionDirection::LEFT)
		{
			frame = RECT{ 0, 0, 0, 0 };
		}
		if (map->map[mapPos.y][mapPos.x - 2].destructibleWall)
		{
			for (int i = 0; i < map->walls.size(); i++)
			{
				if (map->walls[i]->GetCoord()->x == mapPos.x - 2 && map->walls[i]->GetCoord()->y == mapPos.y)
				{
					map->walls.erase(map->walls.begin() + i);
					map->map[mapPos.y][mapPos.x - 2].existWall = false;
					score += 15;
				}
			}
		}
	}

	if (map->map[mapPos.y - 2][mapPos.x].existWall)
	{
		if (dir == EExplosionDirection::MID_TOP || dir == EExplosionDirection::TOP)
		{
			frame = RECT{ 0, 0, 0, 0 };
		}
		if (map->map[mapPos.y - 2][mapPos.x].destructibleWall)
		{
			for (int i = 0; i < map->walls.size(); i++)
			{
				if (map->walls[i]->GetCoord()->x == mapPos.x && map->walls[i]->GetCoord()->y == mapPos.y - 2)
				{
					map->walls.erase(map->walls.begin() + i);
					map->map[mapPos.y - 2][mapPos.x].existWall = false;
					score += 15;
				}
			}
		}
	}

	if (map->map[mapPos.y + 2][mapPos.x].existWall)
	{
		if (dir == EExplosionDirection::MID_BOTTOM || dir == EExplosionDirection::BOTTOM)
		{
			frame = RECT{ 0, 0, 0, 0 };
		}
		if (map->map[mapPos.y + 2][mapPos.x].destructibleWall)
		{
			for (int i = 0; i < map->walls.size(); i++)
			{
				if (map->walls[i]->GetCoord()->x == mapPos.x && map->walls[i]->GetCoord()->y == mapPos.y + 2)
				{
					map->walls.erase(map->walls.begin() + i);
					map->map[mapPos.y + 2][mapPos.x].existWall = false;
					score += 15;
				}
			}
		}
	}


	if (map->map[mapPos.y][mapPos.x + 1].existWall)
	{
		if (dir == EExplosionDirection::MID_RIGHT || dir == EExplosionDirection::RIGHT)
		{
			frame = RECT{ 0, 0, 0, 0 };
		}
		if (map->map[mapPos.y][mapPos.x + 1].destructibleWall)
		{
			for (int i = 0; i < map->walls.size(); i++)
			{
				if (map->walls[i]->GetCoord()->x == mapPos.x + 1 && map->walls[i]->GetCoord()->y == mapPos.y)
				{
					map->walls.erase(map->walls.begin() + i);
					map->map[mapPos.y][mapPos.x + 1].existWall = false;
					score += 15;
				}
			}
		}
	}

	if (map->map[mapPos.y][mapPos.x - 1].existWall)
	{
		if (dir == EExplosionDirection::MID_LEFT || dir == EExplosionDirection::LEFT)
		{
			frame = RECT{ 0, 0, 0, 0 };
		}
		if (map->map[mapPos.y][mapPos.x - 1].destructibleWall)
		{
			for (int i = 0; i < map->walls.size(); i++)
			{
				if (map->walls[i]->GetCoord()->x == mapPos.x - 1 && map->walls[i]->GetCoord()->y == mapPos.y)
				{
					map->walls.erase(map->walls.begin() + i);
					map->map[mapPos.y][mapPos.x - 1].existWall = false;
					score += 15;
				}
			}
		}
	}

	if (map->map[mapPos.y - 1][mapPos.x].existWall)
	{
		if (dir == EExplosionDirection::MID_TOP || dir == EExplosionDirection::TOP)
		{
			frame = RECT{ 0, 0, 0, 0 };
		}
		if (map->map[mapPos.y - 1][mapPos.x].destructibleWall)
		{
			for (int i = 0; i < map->walls.size(); i++)
			{
				if (map->walls[i]->GetCoord()->x == mapPos.x && map->walls[i]->GetCoord()->y == mapPos.y - 1)
				{
					map->walls.erase(map->walls.begin() + i);
					map->map[mapPos.y - 1][mapPos.x].existWall = false;
					score += 15;
				}
			}
		}
	}

	if (map->map[mapPos.y + 1][mapPos.x].existWall)
	{
		if (dir == EExplosionDirection::MID_BOTTOM || dir == EExplosionDirection::BOTTOM)
		{
			frame = RECT{ 0, 0, 0, 0 };
		}
		if (map->map[mapPos.y + 1][mapPos.x].destructibleWall)
		{
			for (int i = 0; i < map->walls.size(); i++)
			{
				if (map->walls[i]->GetCoord()->x == mapPos.x && map->walls[i]->GetCoord()->y == mapPos.y + 1)
				{
					map->walls.erase(map->walls.begin() + i);
					map->map[mapPos.y + 1][mapPos.x].existWall = false;
					score += 15;
				}
			}
		}
	}
}