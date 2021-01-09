#pragma once
#include "SDL.h"
#include "Types.h"
#include "Renderer.h"

class InputManager
{
private:
	InputManager();
	static InputManager* input;
	InputData _input;

public:
	~InputManager();
	static InputManager* GetInstance() { if (input == nullptr) { input = new InputManager; } return input; }

	void Update();
	InputData* GetInput() { return &_input; }
};