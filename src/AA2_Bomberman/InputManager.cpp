#include "InputManager.h"

InputManager* InputManager::input = nullptr;

InputManager::InputManager() {}
InputManager::~InputManager() {}

void InputManager::Update()
{
	_input.SetFalseKeyDown();

#pragma region INPUT HANDLER
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			_input.SetKeyValue(EInputKeys::QUIT, true);
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) _input.SetKeyValue(EInputKeys::ESC, true);
			if (event.key.keysym.sym == SDLK_LEFT) _input.SetKeyValue(EInputKeys::LEFT, true);
			if (event.key.keysym.sym == SDLK_RIGHT) _input.SetKeyValue(EInputKeys::RIGHT, true);
			if (event.key.keysym.sym == SDLK_UP) _input.SetKeyValue(EInputKeys::UP, true);
			if (event.key.keysym.sym == SDLK_DOWN) _input.SetKeyValue(EInputKeys::DOWN, true);
			if (event.key.keysym.sym == SDLK_a) _input.SetKeyValue(EInputKeys::A, true);
			if (event.key.keysym.sym == SDLK_d) _input.SetKeyValue(EInputKeys::D, true);
			if (event.key.keysym.sym == SDLK_w) _input.SetKeyValue(EInputKeys::W, true);
			if (event.key.keysym.sym == SDLK_s) _input.SetKeyValue(EInputKeys::S, true);
			if (event.key.keysym.sym == SDLK_SPACE) _input.SetKeyValue(EInputKeys::SPACE, true);
			if (event.key.keysym.sym == SDLK_RCTRL) _input.SetKeyValue(EInputKeys::RIGHT_CTRL, true);
			break;
		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_ESCAPE) _input.SetKeyValue(EInputKeys::ESC, false);
			if (event.key.keysym.sym == SDLK_LEFT) _input.SetKeyValue(EInputKeys::LEFT, false);
			if (event.key.keysym.sym == SDLK_RIGHT) _input.SetKeyValue(EInputKeys::RIGHT, false);
			if (event.key.keysym.sym == SDLK_UP) _input.SetKeyValue(EInputKeys::UP, false);
			if (event.key.keysym.sym == SDLK_DOWN) _input.SetKeyValue(EInputKeys::DOWN, false);
			if (event.key.keysym.sym == SDLK_a) _input.SetKeyValue(EInputKeys::A, false);
			if (event.key.keysym.sym == SDLK_d) _input.SetKeyValue(EInputKeys::D, false);
			if (event.key.keysym.sym == SDLK_w) _input.SetKeyValue(EInputKeys::W, false);
			if (event.key.keysym.sym == SDLK_s) _input.SetKeyValue(EInputKeys::S, false);
			if (event.key.keysym.sym == SDLK_SPACE) _input.SetKeyValue(EInputKeys::SPACE, false);
			if (event.key.keysym.sym == SDLK_RCTRL) _input.SetKeyValue(EInputKeys::RIGHT_CTRL, false);
			break;
		case SDL_MOUSEMOTION:
			_input.SetMouseCoords(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) _input.SetKeyValue(EInputKeys::MOUSE_LEFT, true);
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) _input.SetKeyValue(EInputKeys::MOUSE_LEFT, false);
			break;
		default:
			break;
		}
	}
#pragma endregion
}
