#include "BlockComponent.h"
#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "Object.h"

BlockComponent::BlockComponent()
{
}

BlockComponent::~BlockComponent()
{
}

bool BlockComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	bodyComponent = owner->getComponent<BodyComponent>();
	spriteComponent = owner->getComponent<SpriteComponent>();


	if (!(bodyComponent && spriteComponent))
	{
		printf("Block Component failed to initialize");
		exit(1);
	}


	if (!(bodyComponent && spriteComponent))
	{
		printf("Block Component failed to initialize");
		exit(1);
	}

	
	return(true);
}

Object* BlockComponent::update(float dt)
{
	/*
	it's a block.  it doesn't really do much.
	*/
	return(NULL);
}

void BlockComponent::finish()
{
}
