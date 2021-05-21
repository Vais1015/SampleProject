#pragma once
#include "SDL_mixer.h"
#include <vector>
#include <string>

class SE
{
public:
	SE(std::string se,int volume = 120);
	~SE();

	void MakeSound();

private:
	Mix_Chunk* mSE;
};