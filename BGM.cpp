#include "BGM.h"
#include "Actor.h"

BGM::BGM(Actor* owner)
	:Component(owner)
	, mBGM(nullptr)
{

}

BGM::~BGM()
{
	Mix_FreeMusic(mBGM);
}

//	まずはSetSoundでファイルを読み込む
//	Volumeは0--128の間
//	無限ループで再生
void BGM::StartBGM(std::string bgm, int volume)
{
	mBGM = Mix_LoadMUS(bgm.c_str());
	
	(void)Mix_VolumeMusic(volume);

	Mix_FadeInMusic(mBGM, -1, 1000);
}

void BGM::StopBGM()
{
	(void)Mix_FadeOutMusic(500);
}
