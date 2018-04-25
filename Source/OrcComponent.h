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
	void setWallHit(bool wasHit) { wallHit = wasHit; }
	void finish();
private:

	BodyComponent* bodyComponent;
	SpriteComponent* spriteComponent;
	PhysicsDevice* pDevice;
	int orcHeight;
	int orcWidth;
	bool wallHit;
};
