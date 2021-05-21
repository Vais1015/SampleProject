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
}
