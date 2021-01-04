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

	int i = 0;
	int j = 0;
	std::string line;
	for (rapidxml::xml_node<>* pNode = pRoot->first_node("Level1"); pNode; pNode = pNode->next_sibling())
	{
		for (rapidxml::xml_node<>* pNodeI = pNode->first_node(); pNodeI; pNodeI = pNodeI->next_sibling())
		{
			for (rapidxml::xml_node<>* pNodeA = pNodeI->first_node(); pNodeA; pNodeA = pNodeA->next_sibling())
			{
				std::string str(pNodeA->name());
				if (str == "Player1")
				{
					i = atoi(pNodeA->first_node()->first_attribute()->next_attribute()->value());
					j = atoi(pNodeA->first_node()->first_attribute()->value());
					map[i][j].player1 = true;
					map[i][j].p1.position.x = j;
					map[i][j].p1.position.y = i;
					map[i][j].p1.hp = atof(pNodeA->first_attribute()->value());
				}
				else if (str == "Player2")
				{
					i = atoi(pNodeA->first_node()->first_attribute()->next_attribute()->value());
					j = atoi(pNodeA->first_node()->first_attribute()->value());
					map[i][j].player2 = true;
					map[i][j].p2.position.y = i;
					map[i][j].p2.position.x = j;
					map[i][j].p2.hp = atof(pNodeA->first_attribute()->value());
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

void Map::Update()
{
	/*for (int i = 0; i < numRows; i++)
	{
		for (int j = 0; j < numCols; j++)
		{

		}
	}*/
}

void Map::Draw() 
{
	for (Wall* w : walls)
	{
		Renderer::GetInstance()->PushSprite(T_WALL, w->GetFrame(), w->GetPosition());
	}
}

void Map::AddWalls()
{
	for (int i = 0; i < numRows; i++)
		for (int j = 0; j < numCols; j++)
		{
			if (map[i][j].existWall)
			{
				if (map[i][j].destructibleWall == false)
				{
					Renderer::GetInstance()->LoadTexture(T_WALL, "../../res/img/items.png");
					Wall* w = new Wall({ map[i][j].wallPosition.x, map[i][j].wallPosition.y, 48, 48 });
					w->SetWallValues(Renderer::GetInstance()->GetTextureSize(T_WALL).x, Renderer::GetInstance()->GetTextureSize(T_WALL).y, 3, 2);
					walls.push_back(std::move(w));
				}
				else
				{
					/*Renderer::GetInstance()->LoadTexture(T_DESTRUCTIBLE_WALL, "../../res/img/items.png");
					Wall* w = new Wall({ map[i][j].wallPosition.x, map[i][j].wallPosition.y, 48, 48 });
					w->SetWallValues(Renderer::GetInstance()->GetTextureSize(T_WALL).x, Renderer::GetInstance()->GetTextureSize(T_WALL).y, 3, 2);
					walls.push_back(std::move(w));*/
				}
			}
		}
}