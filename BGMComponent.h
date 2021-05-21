#pragma once
#include "Component.h"
#include "SDL_mixer.h"
#include <string>

class BGMComponent : public Component
{
public:
	BGMComponent(class Actor*);
	~BGMComponent();

	void StartBGM(std::string bgm, int volume = 70);
	void StopBGM();

private:
	Mix_Music* mBGM;
};