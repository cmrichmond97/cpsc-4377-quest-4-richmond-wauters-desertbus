#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "Definitions.h"
#include "../ThirdParty/SDL2-2.0.7/include/SDL.h"
#include <vector>


class InputDevice
{
public:
	InputDevice();
	~InputDevice();
	bool initialize();
	bool getEvent(GAME_EVENT);
	void update();


private:
	SDL_Event* event;
	std::vector<bool> keysPressed;
	
};









#endif