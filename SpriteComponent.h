#pragma once
#include "Component.h"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
	//drawOrder‚Ì”‚ª¬‚³‚¢‚Ù‚Ç‘‚­XV
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
