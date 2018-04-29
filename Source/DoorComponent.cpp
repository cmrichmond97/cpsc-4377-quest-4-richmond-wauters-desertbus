#include "DoorComponent.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "InventoryComponent.h"
#include "Object.h"
#include "Blackboard.h"

DoorComponent::DoorComponent()
{
}

DoorComponent::~DoorComponent()
{
}

bool DoorComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	bodyComponent = owner->getComponent<BodyComponent>();
	spriteComponent = owner->getComponent<SpriteComponent>();

	if (!(bodyComponent && spriteComponent))
	{
		printf("Door Component failed to initialize");
		exit(1);
	}
	owner->getComponent<BodyComponent>()->setState(CLOSED);
	return(true);
}

Object * DoorComponent::update(float dt)
{
	Object* player = owner->getBlackboard()->getPlayer();
	InventoryComponent* invComp = player->getComponent<InventoryComponent>();
	BodyComponent* playerBody = player->getComponent<BodyComponent>();
	if (owner->getBlackboard()->getLevel() == 1)
	{
		if (invComp->getHasLoot(COUCH) && invComp->getHasLoot(BED) && invComp->getHasLoot(TABLE))
		{
			this->setOpened(true);
		}
	}
	else
	{
		if (playerBody->getPositionPtr()->y <= 112)
		{
			this->setOpened(true);
		}
	}
	return nullptr;
}

void DoorComponent::setOpened(bool open)
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

void DoorComponent::finish()
{
}
