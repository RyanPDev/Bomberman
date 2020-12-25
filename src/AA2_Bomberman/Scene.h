#pragma once
#include "Renderer.h"

class Scene
{
public:
	virtual void Update() = 0;
	virtual void Draw() = 0;

	ESceneState GetSceneState();
};