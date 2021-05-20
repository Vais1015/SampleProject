#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include <vector>
#include <string>

class SelectMenu : public Actor
{
public:
	SelectMenu(class Game* game);

	//	Getter
	bool GetCanInput() const;
	bool GetIsTop() const;

	//	Setter
	void SetTextures(std::string tb, std::string t, std::string bb, std::string b);
	void SetMenuVisualization(bool visualization);

private:
	class SelectSpriteComponent* ssc;
};

class SelectSpriteComponent : public SpriteComponent
{
public:
	SelectSpriteComponent(class Actor* owner, int drawOrder = 200);

	void ProcessInput(const uint8_t* keyState) override;
	void Draw(SDL_Renderer* renderer) override;

	//	�X�^�[�g���j���[�Ō��肪�����ꂽ�Ƃ��ɌĂ΂��֐�
	bool GetCanInput() const;
	bool GetIsTop() const;
	
	//	Setter
	void SetTextures(std::string tb, std::string t, std::string bb,  std::string b);
	void SetMenuVisualization(bool visualization);

private:
	//	�L�[���͂̑ҋ@����
	float mInterval = 0.2f;	//�P�ʕb
	bool mCanInput;

	//�I�����̏����i�[����\����
	struct SelectMenuTexture
	{
		SDL_Texture* nowSelTex;
		SDL_Texture* notSelTex;
		bool isSelecting;
		bool isTop;
		Vector2 pos;
	};

	//	�ǂݍ��މ摜�ւ̃p�X
	std::vector<std::string> mNowSelFilePath;
	std::vector<std::string> mNotSelFilePath;

	//	�ǂݍ��񂾃e�N�X�`���Ə����܂Ƃ߂�����
	std::vector<SelectMenuTexture> mSelectMenuTextures;

	//	�I��ł���e�N�X�`���ւ̃C�e���[�^�[
	std::vector<SelectMenuTexture>::iterator mNowTexItr;
};