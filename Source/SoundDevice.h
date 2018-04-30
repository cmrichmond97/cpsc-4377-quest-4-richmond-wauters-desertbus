#pragma once

#include "Definitions.h"
#include "../ThirdParty/SDL2_mixer-2.0.0/include/SDL_mixer.h"
#include <string>

class AssetLibrary;

class SoundDevice {
public:
	~SoundDevice();
	bool initialize(AssetLibrary* newLibrary);
	void Shutdown();

	bool PlaySound(std::string sound, int numLoops);
	bool PlaySound(std::string sound, int numLoops, int channel);

	void SetBackground(std::string background);

private:

AssetLibrary *library;
};