#include "BodyComponent.h"
#include "SpriteComponent.h"
#include "PhysicsDevice.h"
#include "AssetLibrary.h"
#include "Object.h"

BodyComponent::BodyComponent()
{
}

BodyComponent::~BodyComponent()
{
}

bool BodyComponent::initialize(GAME_OBJECTFACTORY_INITIALIZERS inits)
{
	owner = inits.owner;
	pDevice = inits.pDevice;
	physics = inits.assetLibrary->getObjectPhysics(owner->getType());
	owner->getComponent<SpriteComponent>()->initialize(inits);
	pDevice->createFixture(owner, physics, inits);
	position = inits.startPos;
	dimensions = physics.dimensions;


	return(true);
}

GAME_VEC* BodyComponent::getPositionPtr()
{
	
	return(pDevice->getPosition(owner));
}

GAME_FLT BodyComponent::getAngle()
{
	return pDevice->getAngle(owner);
}

void BodyComponent::setAngle(GAME_FLT newAngle)
{
	pDevice->setAngle(owner, newAngle);
}

GAME_VEC BodyComponent::getVelocity()
{
	return(pDevice->getVelocity(owner));
}

ANIM_STATE BodyComponent::getState()
{
	return(state);
}

void BodyComponent::setState(ANIM_STATE newState)
{
	state = newState;
}

void BodyComponent::start()
{


}

Object* BodyComponent::update(float dt)
{

	return(NULL);
}

void BodyComponent::finish()
{
	pDevice->removeObject(owner);
}

void BodyComponent::setStopPhysics()
{
	pDevice->setStopPhysics(owner);
}

