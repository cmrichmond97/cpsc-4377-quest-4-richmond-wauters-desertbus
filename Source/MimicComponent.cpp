#include "MimicComponent.h"
#include "Object.h"
#include "Blackboard.h"
#include "BodyComponent.h"


MimicComponent::MimicComponent()
{
}

MimicComponent::~MimicComponent()
{
}

bool MimicComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	player = owner->getBlackboard()->getPlayer();
	playerBody = player->getComponent<BodyComponent>();
	bodyComponent = owner->getComponent<BodyComponent>();
	return true;
}

Object * MimicComponent::update(float dt)
{
	if (awake)
	{
		//find angle between mouse and ship
		float targetAngle = (std::atan2(playerBody->getPositionPtr()->y - bodyComponent->getPositionPtr()->y, playerBody->getPositionPtr()->x - bodyComponent->getPositionPtr()->x) * 180 / PI);

		//compare to ship's angle. the -90 is to adjust the sprite. Depending on you sprite, your may need to adjust this
		float diff = targetAngle - bodyComponent->getAngle() - 90;

		//ensures we don't go mor than 180 degres.
		while (diff < -180) {
			diff += 360;
		}
		while (diff > 180) {
			diff -= 360;
		}
		//adjust angle of sprite
		//&&'s are to avoid the sprite from shaking as it is lined up with the mouse or stopped
		if (diff < -2 )
		{
			bodyComponent->setAngle(bodyComponent->getAngle() + 2);
		}
		else if (diff > 0 && diff < 179)
		{
			bodyComponent->setAngle(bodyComponent->getAngle() - 2);
		}


		//use distance formula to figure out how far the mouse is from the sprite.
		float approach = distance(playerBody->getPositionPtr(), bodyComponent->getPositionPtr());
	}
	return nullptr;
}

float MimicComponent::distance(GAME_VEC* src1, GAME_VEC* src2)
{
	GAME_VEC diff;
		diff.x = src1->x - src2->x;
		diff.y = src1->y - src2->y;
	return sqrt(diff.x*diff.x + diff.y*diff.y);
}