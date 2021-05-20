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

	//	決定が押されたときに呼ばれる関数
	SpriteType GetSpriteType() const;
	bool GetCanInput() const;

	//	Setter
	void SetCanInput(bool canInput);

private:
	class BattleScene* mBattleScene;

	float mInterval = 0.2f;	//単位秒
	Uint32 mInputTime;
	bool mCanInput;

	enum class SelectingStatus
	{
		SELECTING,
		NOT_SELECTING
	};

	//選択肢の情報を格納する構造体
	struct BattleMenuTexture
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
	std::vector<BattleMenuTexture> mBattleMenuTextures;

	//	選んでいるテクスチャへのイテレーター
	std::vector<BattleMenuTexture>::iterator mNowTexItr;

	//	現在選んでいるスプライトのタイプ
	SpriteType mNowSpriteType;

	//	コンストラクタで呼ばれる関数
	void SetFilePath();
	void SetTitleMenuTextures();
};