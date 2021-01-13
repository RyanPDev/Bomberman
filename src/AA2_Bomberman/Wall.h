#pragma once
#include "Object.h"
#include "Types.h"

class Wall : public Object
{
public:
	enum class EWallType { NONE = -1, WALL, DESTRUCTIBLE_WALL, DESTROYED_WALL, COUNT };

private:
	EWallType type;

public:
	Wall(RECT);
	~Wall();

	void SetValues(int, int, int, int, EWallType);

	const EWallType GetType() { return type; }
};