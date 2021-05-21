#pragma once
#include "Component.h"
#include "SDL_mixer.h"
#include <string>

class BGM : public Component
{
public:
	//	適当なアクターに接続すること
	BGM(class Actor*);
	~BGM();

	void StartBGM(std::string bgm, int volume = 70);
	void StopBGM();

private:
	Mix_Music* mBGM;
};