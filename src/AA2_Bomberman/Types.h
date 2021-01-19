#pragma once
#include <math.h>
#include <ctime>
#include <string>
#include "Constants.h"

struct VEC2
{
	int x, y;

	VEC2() : x(0), y(0) {};

	VEC2(int _x, int _y) : x(_x), y(_y) {};

	const VEC2 operator- (const VEC2& v) { return VEC2(x - v.x, y - v.y); };

	//Magnitude
	float mod() { return sqrt(x * x + y * y); };
};

struct RECT
{
	int x, y, w, h;

	RECT() : x(0), y(0), w(0), h(0) {};

	RECT(int _x, int _y, int _w, int _h) : x(_x), y(_y), w(_w), h(_h) {};
};

struct Font {
	const std::string id;
	std::string path;
	int size;
};

struct Color {
	uint8_t r, g, b, a;
};

struct Text {
	std::string id;
	std::string text;
	Color color;
	int w;
	int h;
};

struct Soundtrack {
	std::string path;
};

enum class EInputKeys
{
	LEFT, RIGHT, UP, DOWN, A, D, W, S, SPACE, P,
	ESC, MOUSE_LEFT, MOUSE_RIGHT, RIGHT_CTRL, RETURN, QUIT, NONE, COUNT
};

struct InputData
{
private:
	//Inputs
	bool keyboardPressed[(int)EInputKeys::COUNT] = {};
	bool keyboardKeyDown[(int)EInputKeys::COUNT] = {};
	VEC2 mouseCoords;
	VEC2 screenSize = { SCREEN_WIDTH, SCREEN_HEIGHT };

	//TimeControl
	clock_t lastTime = clock();
	float deltaTime = 0.f;

public:
	void UpdateDeltaTime() {
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
	}

	VEC2 GetMouseCoords() { return mouseCoords; }
	const VEC2* GetScreenSize() const { return &screenSize; }
	inline const float* GetDeltaTime() const { return &deltaTime; }

	void SetScreenSize(VEC2 sSize) { screenSize = sSize; }
	void SetMouseCoords(VEC2 coords) { mouseCoords = coords; }
	void SetMouseCoords(int x, int y) {
		mouseCoords = { x, y };
	}

	bool IsPressed(EInputKeys key) {
		return keyboardPressed[(int)key];
	}
	bool JustPressed(EInputKeys key) {
		return keyboardKeyDown[(int)key];
	}

	void SetKeyValue(EInputKeys key, bool value) {
		if (!keyboardPressed[(int)key]) {
			keyboardKeyDown[(int)key] = value;
		}
		else {
			keyboardKeyDown[(int)key] = false;
		}
		keyboardPressed[(int)key] = value;
	}
	void SetFalseKeyDown() {
		for (int i = 0; i < (int)EInputKeys::COUNT; i++) {
			keyboardKeyDown[i] = false;
		}
	}
};

enum class EDirection { NONE = -1, DOWN, LEFT, RIGHT, UP, COUNT };

enum class EGameScene { GAME, EXIT, MENU, RANKING };

enum class ESceneState { CLICK_PLAY, CLICK_EXIT, CLICK_RANKING, RUNNING };