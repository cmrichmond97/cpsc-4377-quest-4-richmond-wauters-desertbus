#include "KeyComponent.h"


KeyComponent::KeyComponent()
{
}

KeyComponent::~KeyComponent()
{
}

bool KeyComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	keyType = inits.keyType;
	return false;
}

Object * KeyComponent::update(float dt)
{
	return nullptr;
}

void KeyComponent::finish()
{

}

