#pragma once
#include "Definitions.h"
#include "Component.h"

class InputComponent :
	public Component
{
public:
	InputComponent();
	~InputComponent();
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	Object* update(float dt);
	void finish();
	void setWallHit(bool wasHit) { if (wallWait == 0) { wallHit = wasHit; wallWait = 8; } }

private:
	InputDevice* iDevice;
	PhysicsDevice* pDevice;
	SoundDevice* sDevice;
	BodyComponent* bodyComponent;
	SpriteComponent* spriteComponent;

	TiXmlElement* orcInitPtr;
	bool orcSpawnLock = true;
	int wallWait = 0;
	bool wallHit = false;
	GAME_OBJECTFACTORY_INITIALIZERS inits;

};