// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "Component.h"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
	//drawOrderÇÃêîÇ™è¨Ç≥Ç¢ÇŸÇ«ëÅÇ≠çXêV
	SpriteComponent(class Actor*, SDL_RendererFlip flip = SDL_FLIP_NONE, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(SDL_Renderer*);
	virtual void SetTexture(SDL_Texture*);

	SDL_Texture* GetTexture() const { return mTexture; }
	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

protected:
	SDL_Texture* mTexture;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;

private:
	SDL_RendererFlip mFlip;
};
