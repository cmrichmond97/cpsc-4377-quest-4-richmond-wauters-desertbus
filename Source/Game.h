#ifndef GAME_H
#define GAME_H




#include <string>
#include <vector>

#include "tinyxml\tinystr.h"
#include "tinyxml\tinyxml.h"
#include "Definitions.h"

class Timer;
class View;
class AssetLibrary;
class Object;
class GraphicsDevice;
class Texture;
class InputDevice;
class GameObjectFactory;
class PhysicsDevice;
class Blackboard;

class Game
{
public:
	Game();
	~Game();

	bool Initialize(std::string);
	void Reset();
	bool LoadLevel(std::string);
	bool Run();
	bool Update();
	bool Draw();
private:
	Timer* timer;
	View* view;
	AssetLibrary* assetLibrary;

	std::vector<Object*> Objects;

	PhysicsDevice* pDevice;
	GraphicsDevice* gDevice;
	InputDevice* iDevice;
	Blackboard* blackboard;
	std::vector<Object*> objects;
	GameObjectFactory* objectFactory;
	GAME_OBJECTFACTORY_INITIALIZERS inits;
	int level;


};










#endif



