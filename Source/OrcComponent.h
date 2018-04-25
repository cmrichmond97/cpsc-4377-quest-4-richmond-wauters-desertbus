#pragma once
#include "Component.h"


class OrcComponent:
	public Component
{
public:
	OrcComponent();
	~OrcComponent();
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	Object* update(float dt);
	void setWallHit(bool wasHit) { if (wallWait == 0) { wallHit = wasHit; wallWait = 5; } }
	void setLinearVelocity(GAME_VEC appliedForce);
	void finish();
private:

	BodyComponent* bodyComponent;
	SpriteComponent* spriteComponent;
	PhysicsDevice* pDevice;
	int orcHeight;
	int orcWidth;
	bool wallHit = false;
	int wallWait = 0;
	
};
