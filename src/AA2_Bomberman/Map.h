#pragma once
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"

#include <iostream>
#include <sstream>
#include "Types.h"
#include "Wall.h"
#include "Constants.h"
#include "Renderer.h"
#include <vector>

struct Cell
{
	VEC2 wallPosition;
	bool existWall = false;
	bool destructibleWall = false;
	bool player1 = false;
	bool player2 = false;
	
	struct Player
	{
		VEC2 position;
		float hp;
	}p1, p2;
};

class Map
{
public:
	Cell map[11][14];
	std::vector<Wall*> walls;

private:
	int numRows = 11, numCols = 14;

public:
	Map();
	~Map();

	void Update();
	void Draw();
	void AddWalls();
};