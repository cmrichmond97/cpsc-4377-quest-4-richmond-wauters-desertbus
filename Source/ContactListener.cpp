#include <string>
#include "definitions.h"
#include "ContactListener.h"
#include "Object.h"
#include "BodyComponent.h"
#include "InputComponent.h"
#include "InventoryComponent.h"
#include "KeyComponent.h"
#include "ChestComponent.h"
#include "OrcComponent.h"
#include "BanditComponent.h"
#include "Blackboard.h"
#include "DoorComponent.h"


void ContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
	//Grab the two Physics Bodies involved in the Contact
	b2Body* bodyA = contact->GetFixtureA()->GetBody();
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	//Cast them to object pointers
	Object* objectA = static_cast<Object*>(bodyA->GetUserData());
	Object* objectB = static_cast<Object*>(bodyB->GetUserData());

	//find their types
	OBJECT_TYPE objectAType = objectA->getType();
	OBJECT_TYPE objectBType = objectB->getType();





	if (objectAType == PLAYER)
	{

		//if we found a pickupable item, grab it.
		if (objectBType == JUNGLE_KEY ||
			objectBType == SHINY_KEY || 
			objectBType == RUINS_KEY || 
			objectBType == ICE_KEY)
		{

			pickUpKey(objectA, objectB);
		}

		//if we found a chest, try to open it.
		if (objectBType == JUNGLE_CHEST ||
			objectBType == SHINY_CHEST ||
			objectBType == RUINS_CHEST ||
			objectBType == ICE_CHEST)
		{
			openChest(objectA, objectB);
		}

		if (objectBType == BIG_DOOR)
		{
			if (objectB->getComponent<DoorComponent>()->getOpened())
			{
				objectA->getBlackboard()->setGameClear(true);
			}
		}

		//if we found an enemy, we die.
		if (objectBType == BANDIT ||
			objectBType == ORC  ||
			objectBType == MIMIC)
		{
			objectA->kill();
		}

	}
	

	//walls always put the player as object B
	switch (objectBType)
	{
		//	case PLAYER:
		//		//if it is a wall, than set the input component's hit wall value to true.
		//		if (objectAType == BLOCK)
		//		{
		////			objectB->getComponent<InputComponent>()->SetWallHit(true);
		//		}
		//		//otherwise, false.
		//		else
		//		{
		////			objectB->getComponent<InputComponent>()->SetWallHit(false);
		//		}
		//		break;

	case ORC:
		//if it is a wall, than set the input componet's hit wall value to true.
		if (objectAType == BLOCK)
		{
			objectB->getComponent<OrcComponent>()->setWallHit(true);
		}
		//otherwise, false.
		else
		{
			objectB->getComponent<OrcComponent>()->setWallHit(false);
		}
		break;

		//case BANDIT:
		//	//if it is a wall, than set the input componet's hit wall value to true.
		//	if (objectAType == BLOCK)
		//	{
		//		objectB->getComponent<BanditComponent>()->SetWallHit(true);
		//	}
		//	//otherwise, false.
		//	else
		//	{
		//		objectB->getComponent<BanditComponent>()->SetWallHit(false);
		//	}
		//	break;

		//default:
		//	break;
	}
	
}

void ContactListener::PostSolve(b2Contact * contact, const b2ContactImpulse * impulse)
{
	b2Body* bodyB = contact->GetFixtureB()->GetBody();
	Object* objectB = static_cast<Object*>(bodyB->GetUserData());

	GAME_INT forceMultiplier = 1500;
	GAME_VEC appliedForce;
	if (objectB->getType() == ORC)
	{
		appliedForce.y = 0;
		appliedForce.x = (float)cosf(((objectB->getComponent<BodyComponent>()->getState())*PI / 180) - (PI / 2))*forceMultiplier;
		objectB->getComponent<OrcComponent>()->setLinearVelocity(appliedForce);
	}

}

void ContactListener::pickUpKey(Object* player, Object* item)
{

	player->getComponent<InventoryComponent>()->addKey(item);


}

void ContactListener::openChest(Object* player, Object* chest)
{
	ChestComponent* chestComp = chest->getComponent<ChestComponent>();

	InventoryComponent* invComp = player->getComponent<InventoryComponent>();

	KEY_TYPE chestType = chestComp->getChestType();
	bool hasKey = invComp->getHasKey(chestType);

	if (hasKey)
	{
		if (!chestComp->getOpened())
		{
			chestComp->setOpened(true);
			invComp->addLoot(chestComp->getHeldLoot());
		}
	}
}

void ContactListener::finishLevel(Object * player, Object * door)
{
	
}

