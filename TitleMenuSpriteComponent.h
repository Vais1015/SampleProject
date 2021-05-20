#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>
#include <string>

class TitleMenuSpriteComponent :public SpriteComponent
{
public:
	enum class SpriteType
	{
		START,
		END
	};

	TitleMenuSpriteComponent(class Actor* owner, int drawOrder = 200);
	~TitleMenuSpriteComponent();

	void ProcessInput(const uint8_t* keyState) override;
	void Draw(SDL_Renderer* renderer) override;

	//	�X�^�[�g���j���[�Ō��肪�����ꂽ�Ƃ��ɌĂ΂��֐�
	SpriteType GetSpriteType() const { return mNowTexItr->spriteType; }

private:
	//	�L�[���͂̑ҋ@����
	float mInterval = 0.2f;	//�P�ʕb
	Uint32 mInputTime;

	enum class SelectingStatus
	{
		SELECTING,
		NOT_SELECTING
	};

	//�I�����̏����i�[����\����
	struct TitleMenuTexture
	{
		SDL_Texture* nowSelectingTexture;
		SDL_Texture* notSelectingTexture;
		SelectingStatus selectingStatus;
		SpriteType spriteType;
		Vector2 pos;
	};

	//	�ǂݍ��މ摜�ւ̃p�X
	std::vector<std::string> mNowSelFilePath;
	std::vector<std::string> mNotSelFilePath;

	//	�ǂݍ��񂾃e�N�X�`���Ə����܂Ƃ߂�����
	std::vector<TitleMenuTexture> mTitleMenuTextures;

	//	�I��ł���e�N�X�`���ւ̃C�e���[�^�[
	std::vector<TitleMenuTexture>::iterator mNowTexItr;

	//	�R���X�g���N�^�ŌĂ΂��֐�
	void SetFilePath();
	void SetTitleMenuTextures();
};