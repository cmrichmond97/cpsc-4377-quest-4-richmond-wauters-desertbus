#include "Object.h"
#include "Component.h"
#include "BanditComponent.h"
#include "BlockComponent.h"
#include "BodyComponent.h"
#include "ChestComponent.h"
#include "DoorComponent.h"
#include "InputComponent.h"
#include "InventoryComponent.h"
#include "KeyComponent.h"
#include "MimicComponent.h"
#include "OrcComponent.h"
#include "SpriteComponent.h"
#include "Blackboard.h"


Object::Object()
{
}


Object::~Object()
{
	finish();
}

void Object::addComponent(Component* component)
{
	components.push_back(component);
}

bool Object::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	type = inits.type;
	blackboard = inits.blackboard;
	this->getComponent<BodyComponent>()->initialize(inits);//initialize the Body component first because the other components depend on it.
	//note:  DO NOT initialize Sprite Components here.  the body components initialize also initializes the sprite component.
	switch (type)
	{
	case PLAYER:
		this->getComponent<InputComponent>()->initialize(inits);
		this->getComponent<InventoryComponent>()->initialize(inits);
		blackboard->setPlayer(this);
		break;

	case ORC:
		this->getComponent<OrcComponent>()->initialize(inits);
		break;

	case BANDIT:
		this->getComponent<BanditComponent>()->initialize(inits);
		break;

	case BLOCK:
		this->getComponent<BlockComponent>()->initialize(inits);
		break;

	case JUNGLE_KEY:
		inits.keyType = JUNGLE;
		this->getComponent<KeyComponent>()->initialize(inits);
		break;
	case SHINY_KEY:
		inits.keyType = SHINY;
		this->getComponent<KeyComponent>()->initialize(inits);
		break;
	case RUINS_KEY:
		inits.keyType = RUINS;
		this->getComponent<KeyComponent>()->initialize(inits);
		break;
	case ICE_KEY:
		inits.keyType = ICE;
		this->getComponent<KeyComponent>()->initialize(inits);
		break;

	case JUNGLE_CHEST:
		inits.keyType = JUNGLE;
		this->getComponent<ChestComponent>()->initialize(inits);
		break;
	case SHINY_CHEST:
		inits.keyType = SHINY;
		this->getComponent<ChestComponent>()->initialize(inits);
		break;
	case RUINS_CHEST:
		inits.keyType = RUINS;
		this->getComponent<ChestComponent>()->initialize(inits);
		break;
	case ICE_CHEST:
		inits.keyType = ICE;
		this->getComponent<ChestComponent>()->initialize(inits);
		break;
	case MIMIC:
		this->getComponent<MimicComponent>()->initialize(inits);
		break;
	case BIG_DOOR:
		this->getComponent<DoorComponent>()->initialize(inits);
		break;

	default:
		break;
	}
	return (true);
}

Object* Object::update(float dt)
{
	Object* newObject = nullptr;
	for (int i = 0; i < components.size(); i++)
	{
		Object* temp = components[i]->update(dt);
		if (temp)
		{
			newObject = temp;
		}
	}
	return(newObject);
}

void Object::draw()
{
	SpriteComponent* comp = getComponent<SpriteComponent>();
	if (comp)
	{
		comp->draw();
	}
}

bool Object::finish()
{
	for (int i = 0; i < components.size(); i++)
	{
		components[i]->finish();
		delete components[i];
	}
	return(true);
}

OBJECT_TYPE Object::getType()
{
	return (type);
}