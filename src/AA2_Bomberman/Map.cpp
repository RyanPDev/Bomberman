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
	rapidxml::xml_node<>* pNode = pRoot->first_node("Level1");

	int i, j;

	//-->NOM�S ES LLEGEIX EL PRIMER NIVELL

	for (rapidxml::xml_node<>* pNodeI = pNode->first_node("Players"); pNodeI; pNodeI = pNodeI->next_sibling())
	{
		for (rapidxml::xml_node<>* pNodeA = pNodeI->first_node(); pNodeA; pNodeA = pNodeA->next_sibling())
		{
			std::string str(pNodeA->name());
			if (str == "Player1")
			{
				i = atoi(pNodeA->first_node()->first_attribute()->next_attribute()->value());
				j = atoi(pNodeA->first_node()->first_attribute()->value());
				initialPlPos.push_back({ j * 48 + 48, i * 48 + 128 });
				player1Hp = atoi(pNodeA->first_attribute()->value());
			}
			else if (str == "Player2")
			{
				i = atoi(pNodeA->first_node()->first_attribute()->next_attribute()->value());
				j = atoi(pNodeA->first_node()->first_attribute()->value());
				initialPlPos.push_back({ j * 48 + 48, i * 48 + 128 });
				player2Hp = atoi(pNodeA->first_attribute()->value());
			}
			else if (str == "Wall")
			{
				std::string str2(pNodeA->first_attribute()->value());
				i = atoi(pNodeA->first_attribute()->next_attribute()->next_attribute()->value());
				j = atoi(pNodeA->first_attribute()->next_attribute()->value());

				if (str2 == "false") map[i][j].destructibleWall = false;
				else if (str2 == "true") map[i][j].destructibleWall = true;

				map[i][j].existWall = true;
				map[i][j].wallPosition.x = j * 48 + 48;
				map[i][j].wallPosition.y = i * 48 + 128;
			}
		}
	}
	for (int i = 0; i < NUM_ROWS; i++)
		for (int j = 0; j < NUM_COLS; j++)
		{
			map[i][j].cellPosition.x = j * 48 + 48;
			map[i][j].cellPosition.y = i * 48 + 128;
		}
}

Map::~Map()
{
	for (std::vector<Wall*>::iterator i = walls.begin(); i != walls.end(); ++i) {
		delete* i;
	}
	walls.clear();

	initialPlPos.clear();
}

void Map::Update()
{

}

void Map::Draw()
{

}

void Map::AddWalls()
{
	for (int i = 0; i < NUM_ROWS; i++)
	{
		for (int j = 0; j < NUM_COLS; j++)
		{
			if (map[i][j].existWall)
			{
				if (map[i][j].destructibleWall == false)
				{
					Wall* w = new Wall({ map[i][j].wallPosition.x, map[i][j].wallPosition.y, 48, 48 });
					w->SetValues(Renderer::GetInstance()->GetTextureSize(T_WALL).x, Renderer::GetInstance()->GetTextureSize(T_WALL).y, 3, 2, false);
					w->SetCoord({ j, i });
					walls.push_back(std::move(w));
				}
				else
				{
					Wall* w = new Wall({ map[i][j].wallPosition.x, map[i][j].wallPosition.y, 48, 48 });
					w->SetValues(Renderer::GetInstance()->GetTextureSize(T_WALL).x, Renderer::GetInstance()->GetTextureSize(T_WALL).y, 3, 2, true);
					w->SetCoord({ j, i });
					walls.push_back(std::move(w));
				}
			}
		}
	}
}