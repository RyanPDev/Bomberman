#pragma once
#include "Renderer.h"
#include "InputManager.h"
#include "AudioManager.h"

class Scene
{
protected:
	ESceneState sceneState;
	std::string texturePlay;
	std::string textureExit;
	std::string textureSound;
	std::string textureRanking;
public:
	~Scene();
	virtual void Update(EDirection dir) = 0;
	virtual void Draw() = 0;
	virtual void SetTexturePlay(std::string id) { texturePlay = id; }
	virtual void SetTextureExit(std::string id) { textureExit = id; }
	virtual void SetTextureSound(std::string id) { textureSound = id; }
	virtual void SetTextureRanking(std::string id) { textureRanking = id; }
	virtual EDirection GetDirection(EDirection dir) { return dir; }

	ESceneState GetSceneState() { return sceneState; }
	void SetSceneState(ESceneState state) { sceneState = state; }
};