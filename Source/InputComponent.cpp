#include "InputComponent.h"
#include "InputDevice.h"
#include "PhysicsDevice.h"
#include "GameObjectFactory.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "OrcComponent.h"
#include "Object.h"

InputComponent::InputComponent()
{
}

InputComponent::~InputComponent()
{
}

bool InputComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	iDevice = inits.iDevice;
	pDevice = inits.pDevice;
	bodyComponent = owner->getComponent<BodyComponent>();
	spriteComponent = owner->getComponent<SpriteComponent>();

	if (!(bodyComponent && spriteComponent))
	{
		printf("Input Component failed to initialize");
		exit(1);
	}
	
	this->inits = inits;

	return(true);
}

Object* InputComponent::update(float dt)
{
	bool idle = true;//idle represents whether or not the player is performing an action
	Object* newObject = nullptr;

	GAME_VEC velocity = pDevice->getLinearVelocity(owner);
	GAME_INT forceMultiplier = 10;
	GAME_VEC appliedForce;

	if (iDevice->getEvent(GAME_UP))//UP
	{
		idle = false;//the player is performing an action
		if (bodyComponent->getState() != UP)
		{
			bodyComponent->setState(UP);//tell the body component that the player's direction has changed
			pDevice->setAngle(owner, UP);
			spriteComponent->setAnimNumber(0);//tell the sprite component that the player's animation has changed
		}
	}
	else
	{
		if (iDevice->getEvent(GAME_DOWN))//DOWN
		{
			idle = false;//the player is performing an action
			if (bodyComponent->getState() != DOWN)
			{
				bodyComponent->setState(DOWN);//tell the body component that the player's direction has changed
				pDevice->setAngle(owner, DOWN);
				spriteComponent->setAnimNumber(0);//tell the sprite component that the player's animation has changed
			}
		}
	}

	if (iDevice->getEvent(GAME_LEFT))//LEFT
	{
		idle = false;//the player is performing an action
		if (bodyComponent->getState() != LEFT)
		{
			bodyComponent->setState(LEFT);//tell the body component that the player's direction has changed
			pDevice->setAngle(owner, LEFT);
			spriteComponent->setAnimNumber(0);//tell the sprite component that the player's animation has changed
		}
	}
	else
	{
		if (iDevice->getEvent(GAME_RIGHT))//RIGHT
		{
			idle = false;//the player is performing an action
			if (bodyComponent->getState() != RIGHT)
			{
				bodyComponent->setState(RIGHT);//tell the body component that the player's direction has changed
				pDevice->setAngle(owner, RIGHT);
				spriteComponent->setAnimNumber(0);//tell the sprite component that the player's animation has changed
			}
		}
	}




	if (idle)//NA
	{
		if (bodyComponent->getState() != NA)//the player is not perfoming an action
		{
			bodyComponent->setState(NA);//tell the body component that the player's direction has changed
			spriteComponent->setAnimNumber(0);//tell the sprite component that the player's animation has changed
			appliedForce.y = 0.0f;
			appliedForce.x = 0.0f;
			pDevice->setLinearVelocity(owner, appliedForce);

		}
	}
	else
	{
		appliedForce.y = (float)sinf((pDevice->getAngle(owner)*PI / 180) - (PI / 2))*forceMultiplier;
		appliedForce.x = (float)cosf((pDevice->getAngle(owner)*PI / 180) - (PI / 2))*forceMultiplier;


		pDevice->setLinearVelocity(owner, appliedForce);
	}
	return(newObject);
}

void InputComponent::finish()
{
}
