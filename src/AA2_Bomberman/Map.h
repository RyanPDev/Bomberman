#pragma once
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"

#include <iostream>
#include <sstream>
#include "Types.h"

struct Cell
{
	VEC2 wallPosition;
	bool existWall = false;
	bool destructibleWall = false;
	//bool bomb;
	//PowerUp type;
};

class Map
{
private:
	Cell** map;
	int numRows = 11, numCols = 14;

public:
	Map();
	~Map();

	void Update();
	void Draw();
};