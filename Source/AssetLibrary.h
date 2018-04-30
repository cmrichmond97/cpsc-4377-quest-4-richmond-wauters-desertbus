#pragma once

#include <string>
#include <map>
#include <vector>
#include "Definitions.h"
#include "SoundDevice.h"


class GraphicsDevice;
class Texture;
class Component;

class AssetLibrary
{
public:
	AssetLibrary();
	~AssetLibrary();
	Texture* getTexture(OBJECT_TYPE);
	Texture* getTexture(GAME_LOOT);
	std::map<ANIM_STATE, std::vector<SPRITE_CLIP*>*>* getAnimMap(OBJECT_TYPE);
	std::vector<Component*> getComponentList(OBJECT_TYPE);
	GAME_PHYSICS getObjectPhysics(OBJECT_TYPE);
	Mix_Chunk* getSound(std::string sound) { return (soundEffects[sound]); }
	Mix_Music* getMusic(std::string music) { return (backgroundMusic[music]); }
	bool initialize(GraphicsDevice*, std::string);
private:
	std::map<OBJECT_TYPE, Texture*> paths;
	std::map<GAME_LOOT, Texture*> lootPaths;

	std::map<OBJECT_TYPE, std::map<ANIM_STATE, std::vector<SPRITE_CLIP*>*>*> animations;
	std::map<OBJECT_TYPE, GAME_PHYSICS> objectPhysics;
	std::map<OBJECT_TYPE, std::vector<GAME_COMPONENTS_LIST>> componentLists;
	std::map<std::string, Mix_Chunk* > soundEffects;
	std::map<std::string, Mix_Music*> backgroundMusic;
};

