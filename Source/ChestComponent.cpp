#include "ChestComponent.h"
#include "Object.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"

ChestComponent::ChestComponent()
{
}

ChestComponent::~ChestComponent()
{
}

bool ChestComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	bodyComponent = owner->getComponent<BodyComponent>();
	spriteComponent = owner->getComponent<SpriteComponent>();
	chestType = inits.keyType;
	heldLoot = inits.heldLoot;

	if (!(bodyComponent && spriteComponent))
	{
		printf("Chest Component failed to initialize");
		exit(1);
	}
	owner->getComponent<BodyComponent>()->setState(CLOSED);
	return(true);

}

Object * ChestComponent::update(float dt)
{
	return nullptr;
}

void ChestComponent::setOpened(bool open)
{
	opened = open;
	if (open)
	{
		owner->getComponent<BodyComponent>()->setState(OPEN);
	}
	else
	{
		owner->getComponent<BodyComponent>()->setState(CLOSED);

	}
}

void ChestComponent::finish()
{
}
