#pragma once
#include "SpriteComponent.h"
#include "Math.h"
#include "SDL.h"

class BGSpriteComponent : public SpriteComponent
{
public:
	BGSpriteComponent(class Actor* owner,std::vector<std::string> fileName, float scrollSpeed = 0.0f,int drawOrder = 10 );
	~BGSpriteComponent();

	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;

	void SetFilePath(std::vector<std::string> filePath);
	void SetBGTextures();

	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	float GetScrollSpeed() const { return mScrollSpeed; }

private:
	// Struct to encapsulate each bg image and its offset
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};

	std::vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;

	//	ì«Ç›çûÇﬁâÊëúÇ÷ÇÃÉpÉX
	std::vector<std::string> mFilePath;
};