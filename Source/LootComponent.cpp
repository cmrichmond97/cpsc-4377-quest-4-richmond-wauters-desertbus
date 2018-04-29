#include "LootComponent.h"
#include "Object.h"


LootComponent::LootComponent()
{

}

LootComponent::~LootComponent()
{
}

bool LootComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	lootType = inits.heldLoot;
	owner = inits.owner;
	return false;
}

Object * LootComponent::update(float dt)
{
	return nullptr;
}

void LootComponent::finish()
{
}
