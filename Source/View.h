#pragma once

#include "Definitions.h"
class InputDevice;
class Blackboard;
class View
{
public:
	View();
	~View();
	bool initialize(InputDevice*, GAME_FLT, GAME_FLT, Blackboard*);
	bool update(int);
	GAME_VEC getPosition();

private:
	InputDevice* inputDevice;
	Blackboard* blackboard;
	GAME_VEC center;
	GAME_VEC position;
	int screenNo = 1;

};

