#include "BGMComponent.h"
#include "Actor.h"

BGMComponent::BGMComponent(Actor* owner)
	:Component(owner)
	, mBGM(nullptr)
{
	//	Soundの初期化
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024))
	{
		SDL_Log("Audioの初期化に失敗しました:%s", SDL_GetError());
	}
}

BGMComponent::~BGMComponent()
{

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
	Mix_FreeMusic(mBGM);
	Mix_CloseAudio();
}
