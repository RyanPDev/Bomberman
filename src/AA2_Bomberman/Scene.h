#pragma once
#include "Renderer.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Collisions.h"
#include "Player.h"

class Scene
{
protected:
	ESceneState sceneState = ESceneState::RUNNING;
	std::string texturePlay;
	std::string textureExit;
	std::string textureSound;
	std::string textureRanking;
	std::vector<std::string> playerTexture;
	std::vector<std::string> hpTexture;
	std::vector<std::string> powerUpsTexture;
	std::vector<Player*> _players;
	Player* p;
	Map map;
public:
	~Scene();
	virtual void Update(InputData*) = 0;
	virtual void Draw() = 0;
	virtual void SetTexturePlay(std::string id) { texturePlay = id; }
	virtual void SetTextureExit(std::string id) { textureExit = id; }
	virtual void SetTextureSound(std::string id) { textureSound = id; }
	virtual void SetTextureRanking(std::string id) { textureRanking = id; }

	ESceneState GetSceneState() { return sceneState; }
	void SetSceneState(ESceneState state) { sceneState = state; }
};