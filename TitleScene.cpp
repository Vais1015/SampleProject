#include "ImgPath.h"
#include "Game.h"
#include "TitleScene.h"
#include "TitleMenu.h"
#include "Actor.h"
#include "StoryFlag.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include <iostream>

//TitleScene
TitleScene::TitleScene(Game* game,class SceneManager* manager)
	:Scene(game,manager)
{
	std::cout << "Start TitleScene" << std::endl;

	LoadData();
}

TitleScene::~TitleScene()
{
	std::cout << ":::Delete TitleScene" << std::endl;
}

void TitleScene::LoadData()
{
	mTitleMenu = new TitleMenu(mGame);

	Vector2 titlePos = Vector2(mGame->GetWindowWidth() / 2.0f, mGame->GetWindowHeight() / 3.0f);
	LoadActor(IMG_TITLE_LOGO, titlePos, 1.0f);

	if (mGame->GetStoryFlag()->GetCleared())
	{
		LoadBG(IMG_TITLE_BG2);
	}
	else
	{
		LoadBG(IMG_TITLE_BG1);
	}
}

void TitleScene::SceneInput(const uint8_t* keyState)
{
	Scene::SceneInput(keyState);
}

void TitleScene::UpdateScene(float deltaTime)
{
	Scene::UpdateScene(deltaTime);
}

void TitleScene::SceneOutput(SDL_Renderer* renderer)
{
	Scene::SceneOutput(renderer);
}
