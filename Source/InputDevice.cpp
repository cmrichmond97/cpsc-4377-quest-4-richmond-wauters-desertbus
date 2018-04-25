#include "InputDevice.h"
#include <iostream>


InputDevice::InputDevice()
{

}

InputDevice::~InputDevice()
{
}

bool InputDevice::initialize()
{
	event = new SDL_Event();
	if (!event)
	{
		printf("SDL Event could not initialize! SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	for (int i = 0; i < 6; i++)//populate the vector
	{
		keysPressed.push_back(false);
	}
	return(true);
}

bool InputDevice::getEvent(GAME_EVENT event)
{
	return(keysPressed[event]);
}


void InputDevice::update()
{
	if (!SDL_PollEvent(event))
	{

		switch (event->type)
		{
		case SDL_KEYDOWN://Keypress sets the flag
			switch (event->key.keysym.sym)
			{
			case SDLK_UP://up arrow
				keysPressed[GAME_UP] = true;
				break;

			case SDLK_DOWN://down arrow
				keysPressed[GAME_DOWN] = true;
				break;

			case SDLK_LEFT://left arrow
				keysPressed[GAME_LEFT] = true;
				break;

			case SDLK_RIGHT://right arrow
				keysPressed[GAME_RIGHT] = true;
				break;

			default:
				break;
			}
			break;

		case SDL_KEYUP://key release unsets the flag
			switch (event->key.keysym.sym)
			{
			case SDLK_UP://up arrow
				keysPressed[GAME_UP] = false;
				break;

			case SDLK_DOWN://down arrow
				keysPressed[GAME_DOWN] = false;
				break;

			case SDLK_LEFT://left arrow
				keysPressed[GAME_LEFT] = false;
				break;

			case SDLK_RIGHT:// right arrow
				keysPressed[GAME_RIGHT] = false;
				break;

			default:
				break;
			}
			break;

		case SDL_QUIT:
			keysPressed[GAME_QUIT] = true;
			break;

		default:

			break;
		}
	}

}