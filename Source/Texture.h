#pragma once

#include <string>

#include "../ThirdParty/SDL2-2.0.7/include/SDL.h"
#include "../ThirdParty/SDL2_image-2.0.2/include/SDL_image.h"
#include "Definitions.h"

class Texture {

public:
	//Initializes variables
	Texture();

	//Deallocates memory
	~Texture();

	//Loads image at specified path
	bool load(SDL_Renderer* renderer, std::string path, COLOR_KEY key);

	//Deallocates texture
	void free();

	//Renders texture at given point
	void render(SDL_Renderer* renderer, int x, int y, SPRITE_CLIP* spriteClip = NULL);
	void renderEx(SDL_Renderer* renderer, int x, int y, float angle, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();

private:

	//The actual hardware texture
	SDL_Texture* texture;

	//Image dimensions
	int width;
	int height;

};