// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Actor.h"
#include"Game.h"
#include "BGSpriteComponent.h"
#include <iostream>

BGSpriteComponent::BGSpriteComponent(class Actor* owner,std::vector<std::string> fileName, float scrollSpeed, int drawOrder)
	:SpriteComponent(owner,SDL_FLIP_NONE, drawOrder)
	, mScrollSpeed(scrollSpeed)
{
	SetScreenSize(Vector2((float)owner->GetGame()->GetWindowWidth(), (float)owner->GetGame()->GetWindowHeight()));
	SetFilePath(fileName);
	SetBGTextures();
}

BGSpriteComponent::~BGSpriteComponent()
{

}

void BGSpriteComponent::Update(float deltaTime)
{
	for (auto& bg : mBGTextures)
	{
		bg.mOffset.x += mScrollSpeed * deltaTime;
		// If this is completely off the screen, reset offset to
		// the right of the last bg texture
		if (bg.mOffset.x < -mScreenSize.x)
		{
			bg.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
		}
	}
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer)
{
	// Draw each background texture
	for (auto& bg : mBGTextures)
	{
		SDL_Rect r;
		// Assume screen size dimensions
		r.w = static_cast<int>(mScreenSize.x);
		r.h = static_cast<int>(mScreenSize.y);
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(mOwner->GetCentralPosition().x - r.w / 2 + bg.mOffset.x);
		r.y = static_cast<int>(mOwner->GetCentralPosition().y - r.h / 2 + bg.mOffset.y);

		// Draw this background
		SDL_RenderCopy(renderer, bg.mTexture, nullptr, &r);
	}
}

void BGSpriteComponent::SetFilePath(std::vector<std::string> filePath)
{
	for (auto i : filePath)
		mFilePath.push_back(i);
}

void BGSpriteComponent::SetBGTextures()
{
	std::vector<SDL_Texture*> texs;

	for (auto i : mFilePath)
		texs.push_back(mOwner->GetGame()->SetTexture(i));

	BGTexture temp;

	for (unsigned int i = 0; i < texs.size(); ++i)
	{
		temp.mTexture = texs[i];	
		temp.mOffset.x = i * mScreenSize.x;
		temp.mOffset.y = 0;
		mBGTextures.emplace_back(temp);
	}
}
