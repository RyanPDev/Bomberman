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
	std::string ScanCode();
	InputData* GetInput() { return &_input; }
};