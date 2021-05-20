#include "Game.h"
#include "Actor.h"
#include "TitleMenuSpriteComponent.h"
#include <vector>
#include <string>
#include <iostream>

#define IMG_KILL "Assets/Button_Start.png"
#define IMG_KILLBRIGHT "Assets/Button_StartBright.png"
#define IMG_NOTKILL "Assets/Button_End.png"
#define IMG_NOTKILLBRIGHT "Assets/Button_EndBright.png"

TitleMenuSpriteComponent::TitleMenuSpriteComponent(class Actor* owner, int drawOrder)
	:SpriteComponent(owner,SDL_FLIP_NONE, drawOrder)
	,mInputTime(SDL_GetTicks())
{
	std::cout << "Start TitleMenuSpriteComponent" << std::endl;

	SetFilePath();
	SetTitleMenuTextures();
}

TitleMenuSpriteComponent::~TitleMenuSpriteComponent()
{
	std::cout << ":::Delete TitleMenuSpriteComponent" << std::endl;
}

//	S,Wで選択肢を移動
void TitleMenuSpriteComponent::ProcessInput(const uint8_t* keyState)
{
	float interval = (SDL_GetTicks() - mInputTime) / 1000.0f;

	if (interval > mInterval)
	{
		if (keyState[SDL_SCANCODE_S])
		{
			mNowTexItr->selectingStatus = TitleMenuSpriteComponent::SelectingStatus::NOT_SELECTING;

			if (mNowTexItr != mTitleMenuTextures.end() - 1)
				mNowTexItr++;
			else
				mNowTexItr = mTitleMenuTextures.begin();

			mNowTexItr->selectingStatus = TitleMenuSpriteComponent::SelectingStatus::SELECTING;

			mInputTime = SDL_GetTicks();
		}

		if (keyState[SDL_SCANCODE_W])
		{
			mNowTexItr->selectingStatus = TitleMenuSpriteComponent::SelectingStatus::NOT_SELECTING;

			if (mNowTexItr != mTitleMenuTextures.begin())
				mNowTexItr--;
			else
				mNowTexItr = mTitleMenuTextures.end() - 1;

			mNowTexItr->selectingStatus = TitleMenuSpriteComponent::SelectingStatus::SELECTING;

			mInputTime = SDL_GetTicks();
		}
	}
}

//	セレクトされているかを判定した後、適切な画像を表示
void TitleMenuSpriteComponent::Draw(SDL_Renderer* renderer)
{
	for (auto& st : mTitleMenuTextures)
	{
		SDL_Rect r;
		int iw, ih;
		SDL_QueryTexture(st.notSelectingTexture, nullptr, nullptr, &iw, &ih);
		r.w = static_cast<int>(iw);
		r.h = static_cast<int>(ih);
		r.x = static_cast<int>(mOwner->GetCentralPosition().x - r.w / 2 + st.pos.x);
		r.y = static_cast<int>(mOwner->GetCentralPosition().y - r.h / 2 + st.pos.y);

		if (st.selectingStatus == SelectingStatus::SELECTING) {
			SDL_RenderCopy(renderer, st.nowSelectingTexture, nullptr, &r);
		}
		else if (st.selectingStatus == SelectingStatus::NOT_SELECTING) {
			SDL_RenderCopy(renderer, st.notSelectingTexture, nullptr, &r);
		}
	}
}

void TitleMenuSpriteComponent::SetFilePath()
{
	mNowSelFilePath.push_back(IMG_KILLBRIGHT);
	mNowSelFilePath.push_back(IMG_NOTKILLBRIGHT);

	mNotSelFilePath.push_back(IMG_KILL);
	mNotSelFilePath.push_back(IMG_NOTKILL);
}

//	セットしたファイルパスからテクスチャを生成
void TitleMenuSpriteComponent::SetTitleMenuTextures()
{
	std::vector<SDL_Texture*> nowSelTexs;
	std::vector<SDL_Texture*> notSelTexs;

	for (auto i : mNowSelFilePath)
		nowSelTexs.push_back(mOwner->GetGame()->SetTexture(i));

	for (auto i : mNotSelFilePath)
		notSelTexs.push_back(mOwner->GetGame()->SetTexture(i));

	TitleMenuTexture temp;

	//	テクスチャと選択状態、タイプ、位置を設定
	for (unsigned int i = 0; i < notSelTexs.size(); ++i)
	{
	
		temp.nowSelectingTexture = nowSelTexs[i];
		temp.notSelectingTexture = notSelTexs[i];

		temp.selectingStatus = SelectingStatus::NOT_SELECTING;

		temp.pos.x = (float)mOwner->GetGame()->GetWindowWidth() / 2.0f;
		temp.pos.y = (float)(mOwner->GetGame()->GetWindowHeight() / 6.5f) * (i + 4);

		if (i == 0)
			temp.spriteType = TitleMenuSpriteComponent::SpriteType::START;
		else
			temp.spriteType = TitleMenuSpriteComponent::SpriteType::END;

		mTitleMenuTextures.emplace_back(temp);
	}

	mNowTexItr = mTitleMenuTextures.begin();

	if (mNowTexItr->selectingStatus == TitleMenuSpriteComponent::SelectingStatus::NOT_SELECTING)
		mNowTexItr->selectingStatus = TitleMenuSpriteComponent::SelectingStatus::SELECTING;
}