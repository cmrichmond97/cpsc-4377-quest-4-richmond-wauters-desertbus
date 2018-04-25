#pragma once

#include<vector>
#include<map>
#include "Definitions.h"
#include "../ThirdParty/SDL2-2.0.7/include/SDL.h"
#include "Component.h"

class GraphicsDevice;
class Texture;

class SpriteComponent:
	public Component
{
public:
	SpriteComponent();
	~SpriteComponent();
	bool initialize(GAME_OBJECTFACTORY_INITIALIZERS inits);
	void setAnimNumber(int);
	Object* update(float dt);
	void draw();
	Texture* getTexture() { return texture; };
	void finish();
private:
std::map<ANIM_STATE, std::vector<SPRITE_CLIP*>*>* animationsMap; //map of string identifiers of animationSequences to vectors containing the sequences
int animNumber; //integer for storing what sprite number we're on for the current animation Sequence
GraphicsDevice* gDevice;
AssetLibrary* assetLibrary;
BodyComponent* bodyComponent;
View* view;
Texture* texture;
};



