#include "Game.h"
#include "Actor.h"
#include "SelectMenu.h"
#include <iostream>

SelectSpriteComponent::SelectSpriteComponent(class Actor* owner, int drawOrder)
	:SpriteComponent(owner, SDL_FLIP_NONE, drawOrder)
	, mCanInput(false)
{

}

//	S,Wで選択肢を移動
void SelectSpriteComponent::ProcessInput(const uint8_t* keyState)
{
	float interval = (SDL_GetTicks() - mOwner->GetGame()->GetInputTime()) / 1000.0f;

	if (mCanInput && interval > mInterval)
	{
		if (keyState[SDL_SCANCODE_W])
		{
			mNowTexItr->isSelecting = false;

			if (mNowTexItr == mSelectMenuTextures.begin())
			{
				mNowTexItr = mSelectMenuTextures.end() - 1;
			}
			else
			{
				mNowTexItr--;
			}

			mNowTexItr->isSelecting = true;

			mOwner->GetGame()->SetInputTime();
		}

		if (keyState[SDL_SCANCODE_S])
		{
			mNowTexItr->isSelecting = false;

			if (mNowTexItr == mSelectMenuTextures.end() - 1)
			{
				mNowTexItr = mSelectMenuTextures.begin();
			}
			else
			{
				mNowTexItr++;
			}

			mNowTexItr->isSelecting = true;

			mOwner->GetGame()->SetInputTime();
		}
	}
}

//	セレクトされているかを判定した後、適切な画像を表示
void SelectSpriteComponent::Draw(SDL_Renderer* renderer)
{
	int i = 0;

	for (auto& st : mSelectMenuTextures)
	{
		SDL_Rect r;
		int iw, ih;
		SDL_QueryTexture(st.notSelTex, nullptr, nullptr, &iw, &ih);
		r.w = static_cast<int>(iw);
		r.h = static_cast<int>(ih);
		r.x = static_cast<int>(mOwner->GetCentralPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetCentralPosition().y - r.h / 2 - 30 + (100 * i));

		if (st.isSelecting)
		{
			SDL_RenderCopy(renderer, st.nowSelTex, nullptr, &r);
		}
		else if (!st.isSelecting)
		{
			SDL_RenderCopy(renderer, st.notSelTex, nullptr, &r);
		}

		++i;
	}
}

//	Getter
bool SelectSpriteComponent::GetCanInput() const
{
	return mCanInput;
}

bool SelectSpriteComponent::GetIsTop() const
{
	return mNowTexItr->isTop; 
}

//	Setter
void SelectSpriteComponent::SetTextures(std::string tb, std::string t, std::string bb, std::string b)
{
	mNowSelFilePath.push_back(tb);
	mNowSelFilePath.push_back(bb);

	mNotSelFilePath.push_back(t);
	mNotSelFilePath.push_back(b);

	//	セットしたファイルパスからテクスチャを生成
	std::vector<SDL_Texture*> nowSelTexs;
	std::vector<SDL_Texture*> notSelTexs;

	for (auto i : mNowSelFilePath)
		nowSelTexs.push_back(mOwner->GetGame()->SetTexture(i));

	for (auto i : mNotSelFilePath)
		notSelTexs.push_back(mOwner->GetGame()->SetTexture(i));

	SelectMenuTexture temp;

	//	テクスチャと選択状態、タイプ、位置を設定
	for (unsigned int i = 0; i < notSelTexs.size(); ++i)
	{

		temp.nowSelTex = nowSelTexs[i];
		temp.notSelTex = notSelTexs[i];

		temp.isSelecting = false;

		if (i == 0)
		{
			temp.isTop = true;
		}
		else
		{
			temp.isTop = false;
		}

		mSelectMenuTextures.emplace_back(temp);
	}

	mNowTexItr = mSelectMenuTextures.begin();

	if (!mNowTexItr->isSelecting)
	{
		mNowTexItr->isSelecting = true;
	}
}


void SelectSpriteComponent::SetMenuVisualization(bool visualization)
{
	if (visualization)
	{
		for (auto i : mSelectMenuTextures)
		{
			SDL_SetTextureAlphaMod(i.nowSelTex, 255);
			SDL_SetTextureAlphaMod(i.notSelTex, 255);
		}

		mCanInput = true;
	}
	else
	{
		for (auto i : mSelectMenuTextures)
		{
			SDL_SetTextureAlphaMod(i.nowSelTex, 0);
			SDL_SetTextureAlphaMod(i.notSelTex, 0);
		}

		mCanInput = false;
	}
}