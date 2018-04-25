#include "InventoryComponent.h"
#include "KeyComponent.h"
#include "Object.h"

InventoryComponent::InventoryComponent()
{

}

InventoryComponent::~InventoryComponent()
{

}

bool InventoryComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	return(true);
}

Object * InventoryComponent::update(float dt)
{
	return nullptr;
}

bool InventoryComponent::addKey(Object * item)
{

	keys[item->getComponent<KeyComponent>()->getKeyType()] = true;
	item->finish();
	
	return (true);
}

bool InventoryComponent::addLoot(GAME_LOOT loot)
{
	if (!inventory[loot])
	{
		inventory[loot] = true;
		return (true);
	}
	else return(false);
}

void InventoryComponent::finish()
{
}
