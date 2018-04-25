#pragma once
#include "Component.h"


class BlockComponent:
	public Component
{
public:
	BlockComponent();
	~BlockComponent();
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	Object* update(float dt);
	void finish();

private:

	BodyComponent* bodyComponent;
	SpriteComponent* spriteComponent;
};
