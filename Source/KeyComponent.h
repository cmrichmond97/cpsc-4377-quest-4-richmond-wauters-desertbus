#pragma once
#include "Component.h"


class KeyComponent :
	public Component
{
public:
	KeyComponent();
	~KeyComponent();
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	Object* update(float dt);
	KEY_TYPE getKeyType() { return (keyType); };
	void finish();
private:
	KEY_TYPE keyType;
};

