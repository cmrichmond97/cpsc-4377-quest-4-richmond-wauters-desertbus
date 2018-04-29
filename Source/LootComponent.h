#pragma once
#include "Component.h"

class LootComponent:
	public Component
{
public:
	LootComponent();
	~LootComponent();

	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	Object* update(float dt);
	void finish();
	GAME_LOOT getLootType() { return (lootType); }
	GAME_VEC* getPosPtr() { return (&position); }
	void setPos(GAME_VEC* newPos) { position.x = newPos->x; 
									position.y = newPos->y;}

private:
	GAME_VEC position;
	GAME_LOOT lootType;
};


