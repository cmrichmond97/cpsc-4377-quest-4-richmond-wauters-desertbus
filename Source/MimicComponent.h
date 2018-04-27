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
	float distance(GAME_VEC* src1, GAME_VEC* src2);
private:
	bool awake;
	Object* player;
	BodyComponent* playerBody;
	BodyComponent* bodyComponent;
};



