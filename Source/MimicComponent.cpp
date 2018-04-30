#include "MimicComponent.h"
#include "Object.h"
#include "Blackboard.h"
#include "BodyComponent.h"
#include "PhysicsDevice.h"


MimicComponent::MimicComponent()
{
}

MimicComponent::~MimicComponent()
{
}

bool MimicComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	pDevice = inits.pDevice;
	player = owner->getBlackboard()->getPlayer();
	playerBody = player->getComponent<BodyComponent>();
	bodyComponent = owner->getComponent<BodyComponent>();
	owner->getComponent<BodyComponent>()->setState(CLOSED);
	pDevice->setAngle(owner, DOWN);
	return true;
}

Object * MimicComponent::update(float dt)
{
	if (pDevice->getPosition(player)->y <= 112 && awake == false)
	{
		awake = true;
		owner->getComponent<BodyComponent>()->setState(DOWN);
	}
	
	if (awake)
	{ //TODO: Mimic is not pathing properly. need to mess around with it some more.
		GAME_INT forceMultiplier =5;
		//find angle between player and mimic

		float mimicPosPtrX = pDevice->getPosition(owner)->x+24;
		float mimicPosPtrY = pDevice->getPosition(owner)->y+21;
		float playerPosPtrX = pDevice->getPosition(player)->x + 9;
		float playerPosPtrY = pDevice->getPosition(player)->y + 24;
		
		float targetAngle = (std::atan2(playerPosPtrY - mimicPosPtrY, playerPosPtrX - mimicPosPtrY) * 180 / PI);

		//compare to mimic's angle. 
		float diff = targetAngle - pDevice->getAngle(owner);

		//ensures we don't go more than 180 degres.
		while (diff < -180) {
			diff += 360;
		}
		while (diff > 180) {
			diff -= 360;
		}
		//adjust angle of sprite
		
		if (diff < -2 )
		{
			pDevice->setAngle(owner, pDevice->getAngle(owner) - 1);
		}
		else if (diff > 0 && diff < 179)
		{
			pDevice->setAngle(owner, pDevice->getAngle(owner) + 1);
		}


		GAME_VEC appliedForce;

		appliedForce.y = (float)sinf((pDevice->getAngle(owner)*PI / 180) - (PI / 2))*forceMultiplier;
		appliedForce.x = (float)cosf((pDevice->getAngle(owner)*PI / 180) - (PI / 2))*forceMultiplier;
		
		pDevice->setLinearVelocity(owner, appliedForce);
	}
	return nullptr;
}



void MimicComponent::finish()
{
}
