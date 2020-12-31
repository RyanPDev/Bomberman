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

	map = new Cell * [numRows];

	for (int i = 0; i < numRows; i++)
		map[i] = new Cell[numCols];

	/*map = new char* [numRows];
	for (int i = 0; i < numRows; i++)
		map[i] = new char[numCols];*/

	rapidxml::xml_node<>* pRoot = doc.first_node();
	rapidxml::xml_node<>* pNode = pRoot->first_node();

	int i = 0;
	int j = 0;
	bool wall = false;

	for (rapidxml::xml_node<>* pNode = pRoot->first_node()->first_node("Map"); pNode; pNode = pNode->next_sibling())
	{
		std::cout << pNode->name() << ':' << '\n';

		for (rapidxml::xml_node<>* pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
		{
			std::cout << pNodeI->name() << '\n';
			for (rapidxml::xml_attribute<>* pNodeA = pNodeI->first_attribute(); pNodeA; pNodeA = pNodeA->next_attribute())
			{
				i = (int)pNodeA->value();
				j = (int)pNodeA->value();
				std::cout << pNodeA->name() << ':' << pNodeA->value() << '\n';
			}
		};
		std::cout << '\n';
	}
}

Map::~Map()
{
	for (int i = 0; i < numRows; i++)
		delete[] map[i];

	delete[] map;
}

void Map::Update() {}

void Map::Draw() {}