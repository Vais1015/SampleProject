#include "SE.h"

SE::SE(std::string se, int volume)
{
	mSE = Mix_LoadWAV(se.c_str());
	mSE->volume = volume;
}

SE::~SE()
{
	Mix_FreeChunk(mSE);
}

void SE::MakeSound()
{
	Mix_PlayChannel(-1, mSE, 0);
}

