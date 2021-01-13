#include "Wall.h"

Wall::Wall(RECT _position) : Object(_position) {}

Wall::~Wall() {}

void Wall::SetValues(int textWidth, int textHeight, int nCol, int nRow, EWallType _type)
{
	frame.w = textWidth / nCol;
	frame.h = textHeight / nRow;
	switch (_type)
	{
	case Wall::EWallType::DESTRUCTIBLE_WALL:
		type = EWallType::DESTRUCTIBLE_WALL;
		frame.x = frame.w;
		break;
	case Wall::EWallType::DESTROYED_WALL:
		type = EWallType::DESTROYED_WALL;
		frame.x = frame.w * 2;
		break;
	case Wall::EWallType::WALL:
		type = EWallType::WALL;
		frame.x = 0;
		break;
	default:
		break;
	}
}