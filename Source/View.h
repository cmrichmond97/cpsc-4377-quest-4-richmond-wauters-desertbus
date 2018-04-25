#pragma once

#include "Definitions.h"
class InputDevice;
class View
{
public:
	View();
	~View();
	bool initialize(InputDevice*, GAME_FLT, GAME_FLT);
	bool update(int);
	GAME_VEC getPosition();

private:
	InputDevice* inputDevice;
	GAME_VEC center;
	GAME_VEC position;
};

