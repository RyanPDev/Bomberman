#pragma once
#include "Scene.h"

class Menu : public Scene
{
private:
	std::string texturePlay;
	std::string textureExit;
	std::string textureSound;
	std::string textureRanking;

public:
	Menu();
	~Menu();

	void Update(InputManager* input);
	void Draw();
	void SetTexturePlay(std::string id) { texturePlay = id; }
	void SetTextureExit(std::string id) { textureExit = id; }
	void SetTextureSound(std::string id) { textureSound = id; }
};