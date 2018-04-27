#pragma once
#include "Component.h"

class MimicComponent:
	public Component
{
public:
	MimicComponent();
	~MimicComponent();
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	Object* update(float dt);
private:
	bool awake;
};



