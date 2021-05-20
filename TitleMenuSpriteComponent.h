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

	//	スタートメニューで決定が押されたときに呼ばれる関数
	SpriteType GetSpriteType() const { return mNowTexItr->spriteType; }

private:
	//	キー入力の待機時間
	float mInterval = 0.2f;	//単位秒
	Uint32 mInputTime;

	enum class SelectingStatus
	{
		SELECTING,
		NOT_SELECTING
	};

	//選択肢の情報を格納する構造体
	struct TitleMenuTexture
	{
		SDL_Texture* nowSelectingTexture;
		SDL_Texture* notSelectingTexture;
		SelectingStatus selectingStatus;
		SpriteType spriteType;
		Vector2 pos;
	};

	//	読み込む画像へのパス
	std::vector<std::string> mNowSelFilePath;
	std::vector<std::string> mNotSelFilePath;

	//	読み込んだテクスチャと情報をまとめたもの
	std::vector<TitleMenuTexture> mTitleMenuTextures;

	//	選んでいるテクスチャへのイテレーター
	std::vector<TitleMenuTexture>::iterator mNowTexItr;

	//	コンストラクタで呼ばれる関数
	void SetFilePath();
	void SetTitleMenuTextures();
};