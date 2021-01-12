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
	VEC2 cellPosition;
	bool existBomb = false;
};

class Map
{
public:
	Cell map[11][14];
	std::vector<Wall*> walls;
	std::vector<VEC2> initialPlPos;

private:
	std::vector<Map> maps;
	int player1Hp;
	int player2Hp;
	const int NUM_ROWS{ 11 }, NUM_COLS{ 13 };

public:
	Map();
	~Map();

	void Update();
	void Draw();
	void AddWalls();
	inline const int* GetPlayer1Hp()const { return &player1Hp; }
	inline const int* GetPlayer2Hp()const { return &player2Hp; }
};