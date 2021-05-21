#include "BGMComponent.h"
#include "Actor.h"

BGMComponent::BGMComponent(Actor* owner)
	:Component(owner)
	, mBGM(nullptr)
{

}

BGMComponent::~BGMComponent()
{
	Mix_FreeMusic(mBGM);
}

//	まずはSetSoundでファイルを読み込む
//	Volumeは0--128の間
//	無限ループで再生
void BGMComponent::StartBGM(std::string bgm, int volume)
{
	mBGM = Mix_LoadMUS(bgm.c_str());
	
	(void)Mix_VolumeMusic(volume);

	Mix_FadeInMusic(mBGM, -1, 500);
}

void BGMComponent::StopBGM()
{
	(void)Mix_FadeOutMusic(500);
}
