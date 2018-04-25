#pragma once
#include "Component.h"


class BanditComponent:
	public Component
{
public:
	BanditComponent();
	~BanditComponent();
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	Object* update(float dt);
	void finish();

private:

	BodyComponent* bodyComponent;
	SpriteComponent* spriteComponent;
	PhysicsDevice* pDevice;
	int maxSteps = 10;//this will probably end up getting set by the XML once we actually have a level set up.
	int steps = 0;
};
