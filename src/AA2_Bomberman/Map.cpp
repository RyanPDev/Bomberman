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

	rapidxml::xml_node<>* pRoot = doc.first_node();
	rapidxml::xml_node<>* pNode = pRoot->first_node();

	for (rapidxml::xml_node<>* pNode = pRoot->first_node()->first_node("Map"); pNode; pNode = pNode->next_sibling())
	{
		std::cout << pNode->name() << ':' << '\n';

		for (rapidxml::xml_node<>* pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
		{
			for (rapidxml::xml_attribute<>* pNodeA = pNodeI->first_attribute(); pNodeA; pNodeA = pNodeA->next_attribute())
				std::cout << pNodeA->value() << '\n';
		};
		std::cout << '\n';
	}
}

Map::~Map() {}

void Map::Update() {}

void Map::Draw() {}