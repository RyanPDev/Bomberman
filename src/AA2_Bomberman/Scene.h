#pragma once
#include "Renderer.h"

class Scene
{
protected:
	ESceneState sceneState;
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	ESceneState GetSceneState() { return sceneState; }
	void SetSceneState(ESceneState state) { sceneState = state; }
};