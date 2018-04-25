#pragma once
#include "Definitions.h"
#include "Component.h"

class PhysicsDevice;

class BodyComponent:
	public Component
{
public:
	BodyComponent();
	~BodyComponent();
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	GAME_VEC* getPositionPtr();
	GAME_VEC getDimensions() { return dimensions; }
	ANIM_STATE getState();
	void setState(ANIM_STATE);
	void start();
	Object* update(float dt);
	void finish();
private:
	ANIM_STATE state;

	GAME_VEC position;
	PhysicsDevice* pDevice;
	GAME_PHYSICS physics;
	GAME_VEC dimensions;

};

