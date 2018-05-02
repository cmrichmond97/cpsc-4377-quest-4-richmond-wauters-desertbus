#include "ChestComponent.h"
#include "Object.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "SoundDevice.h"

ChestComponent::ChestComponent()
{
}

ChestComponent::~ChestComponent()
{
}

bool ChestComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	sDevice = inits.sDevice;
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
		sDevice->PlaySound("Chest", 0, -1);
	}
	else
	{
		owner->getComponent<BodyComponent>()->setState(CLOSED);

	}
}

void ChestComponent::finish()
{
}
