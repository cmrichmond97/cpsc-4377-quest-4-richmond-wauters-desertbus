#pragma once
#include "Component.h"

class BodyComponent;

class MimicComponent:
	public Component
{
public:
	MimicComponent();
	~MimicComponent();
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	Object* update(float dt);
	void finish();
private:
	bool awake;
	Object* player;
	BodyComponent* playerBody;
	BodyComponent* bodyComponent;
	PhysicsDevice* pDevice;
};



