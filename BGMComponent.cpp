#include "BGMComponent.h"
#include "Actor.h"

BGMComponent::BGMComponent(Actor* owner)
	:Component(owner)
	, mBGM(nullptr)
{
	//	Sound�̏�����
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024))
	{
		SDL_Log("Audio�̏������Ɏ��s���܂���:%s", SDL_GetError());
	}
}

BGMComponent::~BGMComponent()
{

}

//	�܂���SetSound�Ńt�@�C����ǂݍ���
//	Volume��0--128�̊�
//	�������[�v�ōĐ�
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
