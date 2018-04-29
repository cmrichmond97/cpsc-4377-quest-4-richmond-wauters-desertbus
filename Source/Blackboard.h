#pragma once
#include "Definitions.h"

class Blackboard
{
public:
	Blackboard();
	~Blackboard();

	void setPlayer(Object* newPlayer) { player = newPlayer; }
	Object* getPlayer() { return(player); }
	void setGameClear(bool clear) { gameClear = clear; }
	bool getGameClear() { return (gameClear); }

private:
	Object* player;
	bool gameClear;

};

