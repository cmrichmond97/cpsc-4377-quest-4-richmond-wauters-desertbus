#include "PhysicsDevice.h"
#include "OrcComponent.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "Object.h"

OrcComponent::OrcComponent()
{
}

OrcComponent::~OrcComponent()
{
}

bool OrcComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	bodyComponent = owner->getComponent<BodyComponent>();
	spriteComponent = owner->getComponent<SpriteComponent>();
	pDevice = inits.pDevice;

	if (!(bodyComponent && spriteComponent))
	{
		printf("Orc Component failed to initialize");
		exit(1);
	}
	owner->getComponent<BodyComponent>()->setState(LEFT);
	return (true);
}

Object* OrcComponent::update( float dt)
{
	/*
	Orc should walk left and right for its update, changing direction when it hits a block or the edge of the screen
	*/
	if (wallWait > 0)
	{
		wallWait--;
	}

	GAME_VEC velocity = pDevice->getLinearVelocity(owner);
	GAME_INT forceMultiplier = 8;
	GAME_VEC appliedForce;

	switch (bodyComponent->getState()) //Before we change the position (i.e. before the orc moves), check if he's hit a wall
	{

	case LEFT: //if the orc is moving to the left, we need to check collision with the left edge of the screen
		if (wallHit) //if the orc is at or past the left edge of the screen
		{
			pDevice->setAngle(owner, RIGHT);
			bodyComponent->setState(RIGHT); //change the state to RIGHT so the orc turns around
			spriteComponent->setAnimNumber(0);
			wallHit = false;
		}


		break;
	case RIGHT: //if the orc is moving to the right, we need to check collission with the right end of the screen
		if (wallHit) //If the orc is at or past the right edge of the screen
		{
			pDevice->setAngle(owner, LEFT);
			bodyComponent->setState(LEFT); //change the state to LEFT so the orc turns around
			spriteComponent->setAnimNumber(0);
			wallHit = false;
		}
		break;
	}

	appliedForce.y = 0;
	appliedForce.x = (float)cosf(((bodyComponent->getState())*PI / 180) - (PI / 2))*forceMultiplier;
	pDevice->setLinearVelocity(owner, appliedForce);

	return(NULL);
}

void OrcComponent::setLinearVelocity(GAME_VEC appliedForce)
{
	pDevice->setLinearVelocity(owner, appliedForce);
}

void OrcComponent::finish()
{
}
