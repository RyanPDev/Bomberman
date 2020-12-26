#pragma once
#include "SDL.h"
#include "Types.h"
#include "Renderer.h"

class InputManager
{
private:
	InputData _input;

public:
	InputManager();
	~InputManager();

	void Update();
	InputData GetInput() { return _input; }
};