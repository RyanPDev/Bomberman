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

	std::cout << "Nombre de la raiz: " << doc.first_node()->name() << "\n";
}

Map::~Map() {}

void Map::Update() {}

void Map::Draw() {}