#pragma once
#include "SpriteComponent.h"
#include "SDL.h"
#include <vector>

class AnimSpriteComponent :public SpriteComponent 
{
public:
	AnimSpriteComponent(class Actor*, int drawOrder = 100);
	void Update(float deltaTime) override;
	void SetAnimTextures(const std::vector<SDL_Texture*>&);

	float GetAnimFPS() const { return nAnimFPS; }
	void SetAnimFPS(float fps) { nAnimFPS = fps; }
private:
	std::vector<SDL_Texture*> mAnimTextures;
	float mCurrFrame;
	float nAnimFPS;
};