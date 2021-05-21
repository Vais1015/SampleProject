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

//	�܂���SetSound�Ńt�@�C����ǂݍ���
//	Volume��0--128�̊�
//	�������[�v�ōĐ�
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
