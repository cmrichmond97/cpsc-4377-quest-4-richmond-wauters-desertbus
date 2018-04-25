#pragma once
#include "Component.h"



class DoorComponent:
	public Component
{
public:
	DoorComponent();
	~DoorComponent();
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	Object* update(float dt);
	void setOpened(bool open);
	bool getOpened() { return(opened); }
	void finish();


private:
	BodyComponent * bodyComponent;
	SpriteComponent* spriteComponent;
	bool opened;
};

