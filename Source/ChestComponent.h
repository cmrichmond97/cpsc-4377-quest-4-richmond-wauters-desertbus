#pragma once
#include "Component.h"

class BodyComponent;
class SpriteComponent;

class ChestComponent:
	public Component
{
public:
	ChestComponent();
	~ChestComponent();
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	Object* update(float dt);
	KEY_TYPE getChestType() { return chestType; }
	GAME_LOOT getHeldLoot() { return heldLoot; }
	void setOpened(bool open);
	bool getOpened() { return(opened); }
	void finish();
private:

	BodyComponent * bodyComponent;
	SpriteComponent* spriteComponent;
	KEY_TYPE chestType;
	bool opened;
	GAME_LOOT heldLoot;
};

