#pragma once
#include "Object.h"

class PowerUp : public Object
{
public:
	enum class EPowerUpType { NONE = -1, SHIELD, ROLLERS, COUNT };

private:
	EPowerUpType type;

public:
	PowerUp(RECT);
	~PowerUp();

	void SetValues(int, int, int, int, EPowerUpType);
	void Draw(EPowerUpType);
	EPowerUpType GeneratePowerUp();

	const EPowerUpType GetType() { return type; }
};