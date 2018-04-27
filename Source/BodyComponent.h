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
	GAME_FLT getAngle();
	void setAngle(GAME_FLT newAngle);
	GAME_VEC getVelocity();
	ANIM_STATE getState();
	void setState(ANIM_STATE);
	void start();
	Object* update(float dt);
	void finish();
	void setStopPhysics();
private:
	ANIM_STATE state = NA;

	GAME_VEC position;
	PhysicsDevice* pDevice;
	GAME_PHYSICS physics;
	GAME_VEC dimensions;

};

