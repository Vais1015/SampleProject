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

	//	スタートメニューで決定が押されたときに呼ばれる関数
	bool GetCanInput() const;
	bool GetIsTop() const;
	
	//	Setter
	void SetTextures(std::string tb, std::string t, std::string bb,  std::string b);
	void SetMenuVisualization(bool visualization);

private:
	//	キー入力の待機時間
	float mInterval = 0.2f;	//単位秒
	bool mCanInput;

	//選択肢の情報を格納する構造体
	struct SelectMenuTexture
	{
		SDL_Texture* nowSelTex;
		SDL_Texture* notSelTex;
		bool isSelecting;
		bool isTop;
		Vector2 pos;
	};

	//	読み込む画像へのパス
	std::vector<std::string> mNowSelFilePath;
	std::vector<std::string> mNotSelFilePath;

	//	読み込んだテクスチャと情報をまとめたもの
	std::vector<SelectMenuTexture> mSelectMenuTextures;

	//	選んでいるテクスチャへのイテレーター
	std::vector<SelectMenuTexture>::iterator mNowTexItr;
};