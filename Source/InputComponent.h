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
private:
	InputDevice* iDevice;
	PhysicsDevice* pDevice;
	BodyComponent* bodyComponent;
	SpriteComponent* spriteComponent;

	TiXmlElement* orcInitPtr;
	bool orcSpawnLock = true;

	GAME_OBJECTFACTORY_INITIALIZERS inits;

};