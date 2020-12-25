#pragma once
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"

#include <iostream>
#include <sstream>

class Map
{
private:
	char** map;

public:
	Map();
	~Map();

	void Update();
	void Draw();
};