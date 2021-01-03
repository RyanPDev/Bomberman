#include "Map.h"

Map::Map()
{
	rapidxml::xml_document<> doc;
	std::ifstream file("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	/*map = new Cell * [numRows];

	for (int i = 0; i < numRows; i++)
		map[i] = new Cell[numCols];*/

	/*map = new char* [numRows];
	for (int i = 0; i < numRows; i++)
		map[i] = new char[numCols];*/

	rapidxml::xml_node<>* pRoot = doc.first_node();
	rapidxml::xml_node<>* pNode = pRoot->first_node();

	char* x = 0;
	char* y = 0;
	char* z = 0;
	int i = 0;
	int j = 0;
	std::string line;
	for (rapidxml::xml_node<>* pNode = pRoot->first_node()->first_node("Map"); pNode; pNode = pNode->next_sibling())
	{
		//std::cout << pNode->name() << ':' << '\n';

		for (rapidxml::xml_node<>* pNodeI = pNode->first_node(); pNodeI && i < numRows; pNodeI = pNodeI->next_sibling())
		{
			//std::cout << pNodeI->name() << '\n';
			for (rapidxml::xml_attribute<>* pNodeA = pNodeI->first_attribute(); pNodeA && j < numCols && pNodeA->next_attribute() != nullptr; pNodeA = pNodeA->next_attribute()->next_attribute()->next_attribute())
			{
				z = pNodeA->value();
				x = pNodeA->next_attribute()->value();
				y = pNodeA->next_attribute()->next_attribute()->value();
				i = atoi(y);
				j = atoi(x);

				std::string str(z);
				if (str == "false") map[i][j].destructibleWall = false;
				else if (str == "true") map[i][j].destructibleWall = true;

				map[i][j].wallPosition.x = i;
				map[i][j].wallPosition.y = j;
				map[i][j].existWall = true;

				//std::cout << pNodeA->name() << ':' << pNodeA->value() << '\n' << pNodeA->next_attribute()->name() << ':' << pNodeA->next_attribute()->value() << std::endl;
			}
		};
		//std::cout << '\n';
	}

	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numCols; j++)
		{
			//if (map[i][j].destructibleWall) std::cout << "Destructible wall: true || " << std::endl;
			if (map[i][j].existWall)
			{
				if (!map[i][j].destructibleWall)
				{
					std::cout << "Position: " << i << "|" << j << std::endl;
					std::cout << "Destructible wall: false" << std::endl;
					std::cout << "x: " << map[i][j].wallPosition.x << " y: " << map[i][j].wallPosition.y << std::endl;
					std::cout << "--------------------------------" << std::endl;
				}
			}
		}
}

Map::~Map()
{
}

void Map::Update() {}

void Map::Draw() {}