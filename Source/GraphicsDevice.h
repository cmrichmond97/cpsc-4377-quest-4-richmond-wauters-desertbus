/*
* Author:	Keith Bush
*			UALR
*
* Date:		January 31, 2015
*
* File:		GraphicsDevice.h
*
* Purpose:	Declaration of the SDL GraphicsDevice class
*/

#ifndef GRAPHICSDEVICE_H
#define GRAPHICSDEVICE_H

#include "../ThirdParty/SDL2-2.0.7/include/SDL.h"
#include "../ThirdParty/SDL2_image-2.0.2/include/SDL_image.h"

class GraphicsDevice
{

public:
	GraphicsDevice(Uint32, Uint32);
	~GraphicsDevice();

	bool Initialize(bool);
	bool ShutDown();

	void Begin();
	void Present();

	SDL_Renderer* getRenderer();

private:

	//Window(s) to display graphics
	SDL_Window* screen;
	SDL_Renderer* renderer;

	//Parameter
	const Uint32 SCREEN_WIDTH;
	const Uint32 SCREEN_HEIGHT;

};
#endif



