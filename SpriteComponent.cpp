#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include <iostream>

SpriteComponent::SpriteComponent(Actor* owner, SDL_RendererFlip flip, int drawOrder)
	:Component(owner)
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mFlip(flip)
	, mTexWidth(0)
	, mTexHeight(0)
{
	owner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(SDL_Texture* texture) 
{
	mTexture = texture;
	SDL_QueryTexture(mTexture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}

void SpriteComponent::Draw(SDL_Renderer* renderer) 
{
	if (mTexture)
	{
		SDL_Rect r;
		// Scale the width/height by owner's scale
		r.w = static_cast<int>(mTexWidth * mOwner->GetScale());
		r.h = static_cast<int>(mTexHeight * mOwner->GetScale());
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(mOwner->GetCentralPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->GetCentralPosition().y - r.h / 2);

		if (mFlip == SDL_FLIP_NONE)
		{
			// Draw (have to convert angle from radians to degrees, and clockwise to counter)
			SDL_RenderCopyEx(renderer, mTexture, nullptr, &r,
				-Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_NONE);
		}
		else if (mFlip == SDL_FLIP_HORIZONTAL)
		{
			SDL_RenderCopyEx(renderer, mTexture, nullptr, &r,
				-Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_HORIZONTAL);
		}
		else if (mFlip == SDL_FLIP_VERTICAL)
		{
			SDL_RenderCopyEx(renderer, mTexture, nullptr, &r,
				-Math::ToDegrees(mOwner->GetRotation()), nullptr, SDL_FLIP_HORIZONTAL);
		}
	}
}
