#pragma once
#include "Renderer.h"
#include "InputManager.h"
#include "AudioManager.h"

class Scene
{
protected:
	ESceneState sceneState;
public:
	virtual void Update(InputManager input) = 0;
	virtual void Draw() = 0;

	ESceneState GetSceneState() { return sceneState; }
	void SetSceneState(ESceneState state) { sceneState = state; }
};