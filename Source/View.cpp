#include "View.h"
#include "InputDevice.h"


View::View()
{



}


View::~View()
{

}

bool View::initialize(InputDevice* input, GAME_FLT x, GAME_FLT y)
{
	inputDevice = input;

	center.x = SCREEN_WIDTH/2;
	center.y = SCREEN_HEIGHT/2;

	position.x = x;
	position.y = y;

	return(true);
}

bool View::update(int level)
{
	if (inputDevice->getEvent(GAME_UP))
	{
		
	}

	return(true);
}

GAME_VEC View::getPosition()
{
	return (position);
}