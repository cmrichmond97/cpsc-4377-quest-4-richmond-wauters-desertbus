#pragma once
#include "Definitions.h"


class Object;

class Component
{
public:
	Component();
	~Component();
	virtual bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits) = 0;
	virtual Object* update(float dt) = 0;
	virtual void finish() = 0;


protected:
	Object* owner;
};
