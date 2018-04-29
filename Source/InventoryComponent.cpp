#include "InventoryComponent.h"
#include "KeyComponent.h"
#include "Object.h"
#include "GameObjectFactory.h"
#include "Component.h"
#include "LootComponent.h"
#include "AssetLibrary.h"

InventoryComponent::InventoryComponent()
{

}

InventoryComponent::~InventoryComponent()
{

}

bool InventoryComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	presets = inits;
	return(true);
	keys[JUNGLE] = false;
	keys[SHINY] = false;
	keys[RUINS] = false;
	keys[ICE] = false;

	inventory[BED] = nullptr;
	inventory[COUCH] = nullptr;
	inventory[TABLE] = nullptr;
}

Object * InventoryComponent::update(float dt)
{
	GAME_VEC newPos = { SCREEN_WIDTH - 40 , 0 };
	if (inventory[BED])
	{
		inventory[BED]->getComponent<LootComponent>()->setPos(&newPos);
		newPos.y += 40;
		if (inventory[COUCH])
		{
			inventory[COUCH]->getComponent<LootComponent>()->setPos(&newPos);
			newPos.y += 40;
			if (inventory[TABLE])
			{
				inventory[TABLE]->getComponent<LootComponent>()->setPos(&newPos);
			}
		}
		else
		{
			if (inventory[TABLE])
			{
				inventory[TABLE]->getComponent<LootComponent>()->setPos(&newPos);
			}
		}
	}
	else
	{
		if (inventory[COUCH])
		{
			inventory[COUCH]->getComponent<LootComponent>()->setPos(&newPos);
			newPos.y += 40;
			if (inventory[TABLE])
			{
				inventory[TABLE]->getComponent<LootComponent>()->setPos(&newPos);
			}
		}
		else
		{
			if (inventory[TABLE])
			{
				inventory[TABLE]->getComponent<LootComponent>()->setPos(&newPos);
			}
		}
	}




	if (newObject != nullptr)
	{
		Object* tempObject = newObject;
		newObject = nullptr;
		return (tempObject);
	}
	else
		return nullptr;
}

bool InventoryComponent::addKey(Object * item)
{

	keys[item->getComponent<KeyComponent>()->getKeyType()] = true;
	item->kill();	
	return (true);
}

bool InventoryComponent::addLoot(GAME_LOOT loot)
{
	if (!inventory[loot])
	{
		presets.type = LOOT;
		presets.startPos = { 565, 0 };
		presets.heldLoot = loot;
		newObject = presets.factory->create(presets);
		
		inventory[loot] = newObject;
		return (true);
	}
	else return(false);
}

bool InventoryComponent::getHasLoot(GAME_LOOT loot)
{

	if (inventory[loot] != nullptr)
	{
		return true;
	}
	else return false;
}

void InventoryComponent::finish()
{
}
