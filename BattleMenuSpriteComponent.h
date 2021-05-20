#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>
#include <string>

class BattleMenuSpriteComponent :public SpriteComponent
{
public:
	enum class SpriteType
	{
		STRIKE,
		SHOOT
	};

	BattleMenuSpriteComponent(class Actor* owner, class BattleScene* battle, int drawOrder = 200);
	~BattleMenuSpriteComponent();

	void ProcessInput(const uint8_t* keyState) override;
	void Draw(SDL_Renderer* renderer) override;

	//	���肪�����ꂽ�Ƃ��ɌĂ΂��֐�
	SpriteType GetSpriteType() const;
	bool GetCanInput() const;

	//	Setter
	void SetCanInput(bool canInput);

private:
	class BattleScene* mBattleScene;

	float mInterval = 0.2f;	//�P�ʕb
	Uint32 mInputTime;
	bool mCanInput;

	enum class SelectingStatus
	{
		SELECTING,
		NOT_SELECTING
	};

	//�I�����̏����i�[����\����
	struct BattleMenuTexture
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
	std::vector<BattleMenuTexture> mBattleMenuTextures;

	//	�I��ł���e�N�X�`���ւ̃C�e���[�^�[
	std::vector<BattleMenuTexture>::iterator mNowTexItr;

	//	���ݑI��ł���X�v���C�g�̃^�C�v
	SpriteType mNowSpriteType;

	//	�R���X�g���N�^�ŌĂ΂��֐�
	void SetFilePath();
	void SetTitleMenuTextures();
};