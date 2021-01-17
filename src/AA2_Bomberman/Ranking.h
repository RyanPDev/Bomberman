#pragma once
#include "Scene.h"
#include <queue>

class Ranking : public Scene
{
private:
	struct Winner
	{
		int score;
		std::string name;
	};

	//std::priority_queue<Winner> rank;
	//std::priority_queue<Winner> rank;
	std::vector<Winner> rank;
	Winner results[10];

	//Winner rank[10];

public:
	Ranking();
	~Ranking();

	void Update(InputData*);
	void Draw();
	void ReadFile();
	friend bool operator>(const Winner& w1, const Winner& w2 ) { return w1.score > w2.score; }
	//bool Ranking::operator==(const Winner& w1)const;
};