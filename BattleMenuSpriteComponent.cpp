#include "BattleMenuSpriteComponent.h"
#include "Game.h"
#include "BattleScene.h"
#include "Actor.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

#define IMG_STRIKE_PATH "Assets/Button_Strike.png"
#define IMG_STRIKEBRIGHT_PATH "Assets/Button_StrikeBright.png"
#define IMG_SHOOT_PATH "Assets/Button_Shoot.png"
#define IMG_SHOOTBRIGHT_PATH "Assets/Button_ShootBright.png"

BattleMenuSpriteComponent::BattleMenuSpriteComponent(class Actor* owner,class BattleScene* battle, int drawOrder)
	:SpriteComponent(owner, SDL_FLIP_NONE, drawOrder)
	,mBattleScene(battle)
	, mInputTime(SDL_GetTicks())
	, mCanInput(false)
{
	std::cout << "Start BattleMenuSpriteComponent" << std::endl;

	SetFilePath();
	SetTitleMenuTextures();
}

BattleMenuSpriteComponent::~BattleMenuSpriteComponent()
{
	std::cout << ":::Delete TitleMenuSpriteComponent" << std::endl;
}

//	S,Wで選択肢を移動
void BattleMenuSpriteComponent::ProcessInput(const uint8_t* keyState)
{
	float interval = (SDL_GetTicks() - mInputTime) / 1000.0f;

	if (mCanInput)
	{
		if (interval > mInterval)
		{
			if (keyState[SDL_SCANCODE_W])
			{
				mNowTexItr->selectingStatus = BattleMenuSpriteComponent::SelectingStatus::NOT_SELECTING;

				if (mNowTexItr != mBattleMenuTextures.begin())
					mNowTexItr--;
				else
					mNowTexItr = mBattleMenuTextures.end() - 1;

				mNowTexItr->selectingStatus = BattleMenuSpriteComponent::SelectingStatus::SELECTING;

				mInputTime = SDL_GetTicks();
			}

			if (keyState[SDL_SCANCODE_S])
			{
				mNowTexItr->selectingStatus = BattleMenuSpriteComponent::SelectingStatus::NOT_SELECTING;

				if (mNowTexItr != mBattleMenuTextures.end() - 1)
					mNowTexItr++;
				else
					mNowTexItr = mBattleMenuTextures.begin();

				mNowTexItr->selectingStatus = BattleMenuSpriteComponent::SelectingStatus::SELECTING;

				mInputTime = SDL_GetTicks();
			}
		}

		if (keyState[SDL_SCANCODE_SPACE])
		{
			mNowSpriteType = mNowTexItr->spriteType;

			mInputTime = SDL_GetTicks();
			
			SetCanInput(false);
		}
	}
}

//	セレクトされているかを判定した後、適切な画像を表示
void BattleMenuSpriteComponent::Draw(SDL_Renderer* renderer)
{
	//	Inputできる場合は表示、できないなら非表示
	if (mCanInput)
	{
		for (auto i : mBattleMenuTextures)
		{
			SDL_SetTextureAlphaMod(i.notSelectingTexture, 255);
			SDL_SetTextureAlphaMod(i.nowSelectingTexture, 255);
		}
	}
	else
	{
		for (auto i : mBattleMenuTextures)
		{
			SDL_SetTextureAlphaMod(i.notSelectingTexture, 0);
			SDL_SetTextureAlphaMod(i.nowSelectingTexture, 0);
		}
	}

	for (auto& st : mBattleMenuTextures)
	{
		SDL_Rect r;
		int iw, ih;
		SDL_QueryTexture(st.notSelectingTexture, nullptr, nullptr, &iw, &ih);
		r.w = static_cast<int>(iw);
		r.h = static_cast<int>(ih);
		r.x = static_cast<int>(mOwner->GetGame()->GetWindowCentralPos().x - r.w / 2);
		r.y = static_cast<int>( st.pos.y);

		if (st.selectingStatus == SelectingStatus::SELECTING)
		{
			SDL_RenderCopy(renderer, st.nowSelectingTexture, nullptr, &r);
		}
		else if (st.selectingStatus == SelectingStatus::NOT_SELECTING)
		{
			SDL_RenderCopy(renderer, st.notSelectingTexture, nullptr, &r);
		}
	}

	//	選択できないとき、クールタイムを表示
	if (!mCanInput)
	{
		float time = mBattleScene->GetPlayer()->GetCoolDown() - mBattleScene->GetPlayer()->GetFromPreviousAttack();

		std::ostringstream oss;
		oss << std::fixed << std::setprecision(2) << time;

		SDL_Surface* surface = TTF_RenderUTF8_Blended(mBattleScene->GetFont(), oss.str().c_str(), SDL_Color{ 255,255,255,255 });
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

		//	テクスチャの位置と大きさ
		SDL_Rect r;

		SDL_QueryTexture(texture, nullptr, nullptr, &r.w, &r.h);
		r.x = static_cast<int>(mOwner->GetGame()->GetWindowCentralPos().x - (r.w / 2.0f));
		r.y = static_cast<int>(mOwner->GetGame()->GetWindowCentralPos().y - 60);

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderCopy(renderer, texture, nullptr, &r);

		SDL_FreeSurface(surface);
		SDL_DestroyTexture(texture);
	}
}

void BattleMenuSpriteComponent::SetFilePath()
{
	mNowSelFilePath.push_back(IMG_STRIKEBRIGHT_PATH);
	mNowSelFilePath.push_back(IMG_SHOOTBRIGHT_PATH);

	mNotSelFilePath.push_back(IMG_STRIKE_PATH);
	mNotSelFilePath.push_back(IMG_SHOOT_PATH);
}

//	セットしたファイルパスからテクスチャを生成
void BattleMenuSpriteComponent::SetTitleMenuTextures()
{
	std::vector<SDL_Texture*> nowSelTexs;
	std::vector<SDL_Texture*> notSelTexs;

	for (auto i : mNowSelFilePath)
		nowSelTexs.push_back(mOwner->GetGame()->SetTexture(i));

	for (auto i : mNotSelFilePath)
		notSelTexs.push_back(mOwner->GetGame()->SetTexture(i));

	BattleMenuTexture temp;

	//	テクスチャと選択状態、タイプ、位置を設定
	for (unsigned int i = 0; i < notSelTexs.size(); ++i)
	{
		temp.nowSelectingTexture = nowSelTexs[i];
		temp.notSelectingTexture = notSelTexs[i];

		temp.selectingStatus = SelectingStatus::NOT_SELECTING;

		temp.pos.x = (float)mOwner->GetGame()->GetWindowCentralPos().x;
		temp.pos.y = (float)(mOwner->GetGame()->GetWindowHeight() / 6.5f) * (i + 2);

		if (i == 0)
			temp.spriteType = BattleMenuSpriteComponent::SpriteType::STRIKE;
		else
			temp.spriteType = BattleMenuSpriteComponent::SpriteType::SHOOT;

		mBattleMenuTextures.emplace_back(temp);
	}

	mNowTexItr = mBattleMenuTextures.begin();

	if (mNowTexItr->selectingStatus == BattleMenuSpriteComponent::SelectingStatus::NOT_SELECTING)
		mNowTexItr->selectingStatus = BattleMenuSpriteComponent::SelectingStatus::SELECTING;
}


//	Getter
BattleMenuSpriteComponent::SpriteType BattleMenuSpriteComponent::GetSpriteType() const 
{
	return mNowSpriteType; 
}

bool BattleMenuSpriteComponent::GetCanInput() const
{
	return mCanInput; 
}

//	Setter
void BattleMenuSpriteComponent::SetCanInput(bool canInput)
{
	mCanInput = canInput; 
}
