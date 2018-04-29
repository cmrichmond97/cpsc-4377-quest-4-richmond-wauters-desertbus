#include "BanditComponent.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "Object.h"
#include "PhysicsDevice.h"

BanditComponent::BanditComponent()
{
}

BanditComponent::~BanditComponent()
{
}

bool BanditComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	pDevice = inits.pDevice;
	bodyComponent = owner->getComponent<BodyComponent>();
	spriteComponent = owner->getComponent<SpriteComponent>();

	if (!(bodyComponent && spriteComponent))
	{
		printf("Bandit Component failed to initialize");
		exit(1);
	}
	owner->getComponent<BodyComponent>()->setState(DOWN);
	return(true);
}

Object* BanditComponent::update(float dt)
{
	/*
	Bandit should walk in a clockwise square, changing direction after taking X steps
	*/


	GAME_VEC velocity = pDevice->getLinearVelocity(owner);
	GAME_INT forceMultiplier = 10;
	GAME_VEC appliedForce;

	if (steps >= maxSteps) //if the bandit has taken five or more steps, it's time for them to rotate
	{
		//check which way the bandit was moving and turn him in the appropriate direction
		switch (bodyComponent->getState())
		{
		case LEFT: //if he was facing left, turn to move up next
			pDevice->setAngle(owner, UP);
			bodyComponent->setState(UP);
			break;
		case UP: //if he was facing up, turn to move right next
			pDevice->setAngle(owner, RIGHT);
			bodyComponent->setState(RIGHT);
			break;
		case RIGHT: //if he was facing right, turn to move down
			pDevice->setAngle(owner, DOWN);
			bodyComponent->setState(DOWN);
			break;
		case DOWN: //if he was facing down, turn to move left
			pDevice->setAngle(owner, LEFT);
			bodyComponent->setState(LEFT);
			break;
		}
		steps = 0;
		spriteComponent->setAnimNumber(0);
	}
	else steps++;

	appliedForce.y = (float)sinf((bodyComponent->getState()*PI / 180) - (PI / 2))*forceMultiplier;
	appliedForce.x = (float)cosf((bodyComponent->getState()*PI / 180) - (PI / 2))*forceMultiplier;
	pDevice->setLinearVelocity(owner, appliedForce);


	return(NULL);
}

void BanditComponent::finish()
{
}
