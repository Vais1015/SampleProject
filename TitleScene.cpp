#include "ImgPath.h"
#include "Game.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "SelectMenu.h"
#include "Actor.h"
#include "StoryFlag.h"
#include "SpriteComponent.h"
#include "BGSpriteComponent.h"
#include <iostream>

//TitleScene
TitleScene::TitleScene(Game* game, class SceneManager* manager)
	:Scene(game, manager)
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
	//	TitleLogo
	Vector2 titlePos = Vector2(mGame->GetWindowWidth() / 2.0f, mGame->GetWindowHeight() / 3.0f);
	LoadActor(IMG_TITLE_LOGO, titlePos, 1.0f);

	//	TitleBG
	if (mGame->GetStoryFlag()->GetCleared())
	{
		LoadBG(IMG_TITLE_BG2);
	}
	else
	{
		LoadBG(IMG_TITLE_BG1);
	}

	//	TitleMenu
	Actor* temp = new Actor(mGame);
	temp->SetCentralPosition(Vector2(mGame->GetWindowCentralPos().x, mGame->GetWindowCentralPos().y + 100));
	mSM = new SelectSpriteComponent(temp);
	mSM->SetTextures(IMG_START_BRIGHT, IMG_START, IMG_END_BRIGHT, IMG_END);
	mSM->SetMenuVisualization(true);
}

void TitleScene::SceneInput(const uint8_t* keyState)
{
	Scene::SceneInput(keyState);

	if (keyState[SDL_SCANCODE_SPACE])
	{
		if (mSM->GetIsTop())
		{
			mSceneManager->ChangeSceneType(SceneManager::SceneType::ADVENTURE);
		}
		else
		{
			mGame->SetIsRunning(false);
		}
	}
}

void TitleScene::UpdateScene(float deltaTime)
{
	Scene::UpdateScene(deltaTime);
}

void TitleScene::SceneOutput(SDL_Renderer* renderer)
{
	Scene::SceneOutput(renderer);
}
