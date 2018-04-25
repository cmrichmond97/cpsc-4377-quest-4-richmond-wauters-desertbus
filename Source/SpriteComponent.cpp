#include "SpriteComponent.h"
#include "BodyComponent.h"
#include "AssetLibrary.h"
#include "GraphicsDevice.h"
#include "Object.h"
#include "View.h"
#include "Texture.h"

SpriteComponent::SpriteComponent()
{
}

SpriteComponent::~SpriteComponent()
{
}

bool SpriteComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	animationsMap = inits.assetLibrary->getAnimMap(owner->getType());
	texture = inits.assetLibrary->getTexture(owner->getType());
	gDevice = inits.gDevice;
	view = inits.view;
	bodyComponent = owner->getComponent<BodyComponent>();

	if (!bodyComponent)
	{
		printf("Sprite Component failed to initialize");
		exit(1);
	}

	bodyComponent->setState(NA); //start the player in an idle animation



	return(true);
}

void SpriteComponent::setAnimNumber(int newAnimNumber)
{
	animNumber = newAnimNumber;
}

Object * SpriteComponent::update(float dt)
{
	animNumber++;
	if (animNumber >= animationsMap->at(bodyComponent->getState())->size())
	{
		animNumber = 0;
	}
	return(nullptr);
}

void SpriteComponent::draw()
{
	texture->render(gDevice->getRenderer(), bodyComponent->getPositionPtr()->x + view->getPosition().x, bodyComponent->getPositionPtr()->y + view->getPosition().y, animationsMap->at(bodyComponent->getState())->at(animNumber));

}


void SpriteComponent::finish()
{
}
