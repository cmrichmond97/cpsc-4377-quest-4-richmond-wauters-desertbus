#pragma once

#include "../ThirdParty/Box2D/Box2D/Box2D.h"
class Object;
class ContactListener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) {}

	void EndContact(b2Contact* contact) {}

	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);


	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {}

	void pickUpKey(Object* player, Object* item);

	void openChest(Object* player, Object* chest);

	void finishLevel(Object* player, Object* door);
};
