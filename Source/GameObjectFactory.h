#pragma once

#include<vector>

#include"tinyxml\tinyxml.h"
#include"tinyxml\tinystr.h"
#include"Definitions.h"


class GraphicsDevice;
class Object;
class Component;

class GameObjectFactory
{
public:
	GameObjectFactory();
	~GameObjectFactory();
	Object* create( GAME_OBJECTFACTORY_INITIALIZERS);
	Object* create(std::vector<Component*>, GAME_OBJECTFACTORY_INITIALIZERS);
private:

};