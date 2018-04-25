#include "View.h"
#include "InputDevice.h"
#include "Blackboard.h"
#include "Object.h"
#include "BodyComponent.h"


View::View()
{



}


View::~View()
{

}

bool View::initialize(InputDevice* input, GAME_FLT x, GAME_FLT y, Blackboard* bBoard)
{
	inputDevice = input;
	blackboard = bBoard;
	center.x = SCREEN_WIDTH/2;
	center.y = SCREEN_HEIGHT/2;

	position.x = x;
	position.y = y;

	return(true);
}

bool View::update(int level)
{
	if (level == 2)
	{
		if (blackboard->getPlayer()->getComponent<BodyComponent>()->getPositionPtr()->y > SCREEN_HEIGHT)
		{
			if (screenNo == 1)
			{
				position.y += SCREEN_HEIGHT;
			}
		}
		if (blackboard->getPlayer()->getComponent<BodyComponent>()->getPositionPtr()->y < SCREEN_HEIGHT)
		{
			if (screenNo == 2)
			{
				position.y -= SCREEN_HEIGHT;
			}
		}
	}
	return(true);
}

GAME_VEC View::getPosition()
{
	return (position);
}