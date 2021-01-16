#pragma once
#include "Scene.h"

class Menu : public Scene
{
private:
	static std::string level;
public:
	Menu();
	~Menu();

	void Update(InputData*);
	void Draw();
	void SetCurrentLevel(std::string _level) { level = _level; }
	static std::string GetCurrentLevel() { return level; }
};