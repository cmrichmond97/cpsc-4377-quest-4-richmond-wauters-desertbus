#include"GameObjectFactory.h"
#include"AssetLibrary.h"
#include"Object.h"
#include"SpriteComponent.h"
#include"BodyComponent.h"
#include"InputComponent.h"
#include"BlockComponent.h"
#include"BanditComponent.h"
#include"OrcComponent.h"

GameObjectFactory::GameObjectFactory()
{

}

GameObjectFactory::~GameObjectFactory()
{

}
Object* GameObjectFactory::create(GAME_OBJECTFACTORY_INITIALIZERS inits)
{

	Object* newObject = new Object;

	std::vector<Component*> components = inits.assetLibrary->getComponentList(inits.type);

	inits.owner = newObject;
	for (int i = 0; i < components.size(); i++)
	{
		newObject->addComponent(components[i]);
	}
	if (!newObject->initialize(inits))
	{
		printf("Object could not be initialized");
		exit(1);
	}

	return (newObject);
}

Object * GameObjectFactory::create(std::vector<Component*> components, GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	Object* newObject = new Object;
	inits.owner = newObject;
	for (int i = 0; i < components.size(); i++)
	{
		newObject->addComponent(components[i]);
	}
	if (!newObject->initialize(inits))
	{
		printf("Object could not be initialized");
		exit(1);
	}

	return (newObject);
}
