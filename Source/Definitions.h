#pragma once
class Object;
class AssetLibrary;
class GraphicsDevice;
class InputDevice;
class PhysicsDevice;
class View;
class GameObjectFactory;
class BodyComponent;
class SpriteComponent;
class Blackboard;
#include <string>
#include "tinyxml\tinyxml.h"
#include "tinyxml\tinystr.h"

//Basic Types
typedef unsigned int	Uint32;
typedef float			GAME_FLT;
typedef Uint32			GAME_INT;
typedef struct GAME_VEC
{
	float x;
	float y;
	//friend ostream& operator<< (ostream& o, const GAME_VEC& src);
	GAME_VEC& operator+= (const GAME_VEC & src1)
	{
		this->x = src1.x + this->x;
		this->y = src1.y + this->y;
		return *this;
	}

	friend GAME_VEC operator+ (const GAME_VEC & src1, const GAME_VEC & src2)
	{
		return GAME_VEC{ src1.x + src2.x, src1.y + src2.y };
	}
	friend GAME_VEC operator- (const GAME_VEC & src1, const GAME_VEC & src2)
	{
		return GAME_VEC{ src1.x - src2.x, src1.y - src2.y };
	}
	friend bool operator> (const GAME_VEC & src1, int src2)
	{
		if (src1.x > src2 && src1.y > src2)
		{
			return true;
		}
		return false;
	}
	friend bool operator< (const GAME_VEC & src1, int src2)
	{
		if (src1.x < src2 && src1.y < src2)
		{
			return true;
		}
		return false;
	}
	friend bool operator== (const GAME_VEC & src1, const GAME_VEC & src2)
	{
		if (src1.x == src2.x && src1.y == src2.y)
		{
			return true;
		}
		return false;
	}
	friend GAME_VEC abs(GAME_VEC & src)
	{
		return { abs(src.x),abs(src.y) };
	}
} GAME_VEC;

//========================================
//Base Game Constants
//========================================
const GAME_INT SCREEN_WIDTH = 588;
const GAME_INT SCREEN_HEIGHT = 420;
const GAME_INT GAME_FPS = 100;
const GAME_FLT dt = 1/GAME_FPS;

//OBJECT SPEED CONSTANTS
const GAME_INT PLAYER_XSPEED = 10;
const GAME_INT PLAYER_YSPEED = 10;
const GAME_INT ORC_XSPEED = 10;
const GAME_INT ORC_YSPEED = 10;
const GAME_INT BANDIT_XSPEED = 10;
const GAME_INT BANDIT_YSPEED = 10;
//Event Types
enum GAME_EVENT { GAME_NA, GAME_UP, GAME_DOWN, GAME_LEFT, GAME_RIGHT, GAME_QUIT };
enum ANIM_STATE { NA = -1, UP = 0, DOWN = 180, LEFT = 270, RIGHT = 90, CLOSED = 1, OPEN = 2 };
enum OBJECT_TYPE { PLAYER, ORC, BANDIT, BLOCK, JUNGLE_KEY, JUNGLE_CHEST, SHINY_KEY, SHINY_CHEST, RUINS_KEY, RUINS_CHEST, ICE_KEY, ICE_CHEST, BIG_DOOR };
enum KEY_TYPE { JUNGLE, SHINY, RUINS, ICE };
enum GAME_OBJECT_SHAPE { GAME_RECTANGLE, GAME_CIRCLE };
enum GAME_BODY_TYPE { GAME_STATIC, GAME_KINEMATIC, GAME_DYNAMIC };
enum GAME_LOOT { COUCH, BED, TABLE, };
enum GAME_COMPONENTS_LIST {
	BANDIT_COMPONENT,
	BLOCK_COMPONENT,
	BODY_COMPONENT,
	CHEST_COMPONENT,
	DOOR_COMPONENT,
	INPUT_COMPONENT,
	INVENTORY_COMPONENT,
	KEY_COMPONENT,
	ORC_COMPONENT,
	SPRITE_COMPONENT
};


//Constants
const GAME_FLT PI = 3.14159f;


const float fPRV = 10.0f;

typedef struct COLOR_KEY
{
	int r;
	int g;
	int b;
	int a;
}COLOR_KEY;

typedef struct GAME_OBJECTFACTORY_INITIALIZERS
{
	//OBJECT DATA
	Object* owner;
	OBJECT_TYPE type;
	GAME_VEC startPos;
	GAME_FLT angle;
	KEY_TYPE keyType;
	GAME_LOOT heldLoot;

	//DEVICE POINTERS
	AssetLibrary* assetLibrary;
	GraphicsDevice* gDevice;
	TiXmlElement* root;
	InputDevice* iDevice;
	PhysicsDevice* pDevice;
	View* view;
	GameObjectFactory* factory;
	Blackboard* blackboard;

}GAME_OBJECTFACTORY_INITIALIZERS;

typedef struct SPRITE_CLIP
{
	int x;
	int y;
	int h;
	int w;
}SPRITE_CLIP;

typedef struct GAME_PHYSICS
{
	GAME_FLT spinSpeed;
	GAME_BODY_TYPE bodyType;
	GAME_OBJECT_SHAPE objectShape;
	GAME_FLT density;
	GAME_FLT friction;
	GAME_FLT restitution;
	GAME_FLT angularDamping;
	GAME_FLT linearDamping;
	GAME_FLT force;
	bool physicsOn;
	GAME_VEC dimensions;
}GAME_PHYSICS;

inline OBJECT_TYPE objectType_Convert(std::string objectType)
{
	if (objectType == "Player" || objectType == "player")return(PLAYER);
	if (objectType == "Orc" || objectType == "orc")return(ORC);
	if (objectType == "Bandit" || objectType == "bandit")return(BANDIT);
	if (objectType == "Block" || objectType == "block")return(BLOCK);
	if (objectType == "JungleKey" || objectType == "jungleKey")return(JUNGLE_KEY);
	if (objectType == "JungleChest" || objectType == "jungleChest")return(JUNGLE_CHEST);
	if (objectType == "ShinyKey" || objectType == "shinyKey")return(SHINY_KEY);
	if (objectType == "ShinyChest" || objectType == "shinyChest")return(SHINY_CHEST);
	if (objectType == "RuinsKey" || objectType == "ruinsKey")return(RUINS_KEY);
	if (objectType == "RuinsChest" || objectType == "ruinsChest")return(RUINS_CHEST);
	if (objectType == "IceKey" || objectType == "iceKey")return(ICE_KEY);
	if (objectType == "IceChest" || objectType == "iceChest")return(ICE_CHEST);
	if(objectType == "BigDoor" || objectType == "bigDoor")return(BIG_DOOR);
	return OBJECT_TYPE();
}

inline KEY_TYPE keyType_Convert(std::string keyType)
{
	if (keyType == "Jungle" || keyType == "jungle")return(JUNGLE);
	if (keyType == "Shiny" || keyType == "shiny")return(SHINY);
	if (keyType == "Ruins" || keyType == "ruins")return(RUINS);
	if (keyType == "Ice" || keyType == "ICE")return(ICE);
	return KEY_TYPE();
}

inline GAME_LOOT gameLoot_Convert(std::string lootType)
{
	if (lootType == "Couch" || lootType == "couch")return(COUCH);
	if (lootType == "Bed" || lootType == "bed")return(BED);
	if (lootType == "Table" || lootType == "table")return(TABLE);
	return GAME_LOOT();
}