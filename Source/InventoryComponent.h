#pragma once
#include <map>
#include "Component.h"


class InventoryComponent:
	public Component
{
public:
	InventoryComponent();
	~InventoryComponent();
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	Object* update(float dt);
	bool addKey(Object* item);
	bool addLoot(GAME_LOOT loot);
	bool getHasKey(KEY_TYPE type) { return(keys[type]); };
	bool getHasLoot(GAME_LOOT loot) { return inventory[loot]; };
	void finish();
private:
	std::map<KEY_TYPE, bool> keys;
	std::map<GAME_LOOT, bool> inventory;
};

