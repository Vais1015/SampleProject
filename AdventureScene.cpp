#include "ImgPath.h"
#include "Game.h"
#include "SceneManager.h"
#include "AdventureScene.h"
#include "MessageWindow.h"
#include "StoryFlag.h"
#include "BGSpriteComponent.h"
#include "StoryFlag.h"
#include "SelectMenu.h"
#include <sstream>
#include <iostream>

AdventureScene::AdventureScene(class Game* game, SceneManager* manager)
	:Scene(game, manager)
	, mTextNumber(0)
	, sm(nullptr)
	, mDoneVisu(false)
{
	std::cout << "Start AdventureScene" << std::endl;

	LoadData();
}

AdventureScene::~AdventureScene()
{
	mGame->GetMemberSize();
	std::cout << ":::Delete AdventureScene" << std::endl;
}

void AdventureScene::LoadData()
{
	mMessageWindow = new MessageWindow(mGame);

	SetTextNumber();
	SetObject();
}


void AdventureScene::SceneInput(const uint8_t* keyState)
{
	Scene::SceneInput(keyState);

	float interval = (SDL_GetTicks() - mGame->GetInputTime()) / 1000.0f;

	if (mTextNumber == 2)
	{
		if (interval > 0.5f
			&& sm->GetCanInput()
			&& keyState[SDL_SCANCODE_SPACE])
		{
			if (sm->GetIsTop())
			{
				mGame->GetStoryFlag()->SetKillFlag(true);
				mGame->GetSceneManager()->ChangeSceneType(SceneManager::SceneType::ADVENTURE);
			}
			else
			{
				mGame->GetStoryFlag()->SetKillFlag(false);
				mGame->GetSceneManager()->ChangeSceneType(SceneManager::SceneType::ADVENTURE);
			}
		}
	}

	if (mTextNumber == 3 || mTextNumber == 4)
	{
		if (interval > 0.5f
			&& sm->GetCanInput()
			&& keyState[SDL_SCANCODE_SPACE])
		{
			if (sm->GetIsTop())
			{
				GetStoryFlag()->SetSelectedKillFlag(false);
				GetStoryFlag()->SetReated();
				mGame->GetSceneManager()->ChangeSceneType(SceneManager::SceneType::ADVENTURE);
			}
			else
			{
				mGame->GetSceneManager()->ChangeSceneType(SceneManager::SceneType::TITLE);
			}
		}
	}
}

void AdventureScene::UpdateScene(float deltaTime)
{
	Scene::UpdateScene(deltaTime);

	SetNextScene();
}

void AdventureScene::SceneOutput(SDL_Renderer* renderer)
{

	if (mMessageWindow->GetOccupied())
	{
		mMessageWindow->DisplayMessageWindow(renderer);
	}

	Scene::SceneOutput(renderer);
}

//	Getter
StoryFlag* AdventureScene::GetStoryFlag() const 
{
	return mGame->GetStoryFlag(); 
}

//	Setter
void AdventureScene::SetFlag(int textNumber)
{
	mGame->GetStoryFlag()->SetFlag(textNumber); 
}


//	Setter, but private, helper for only LoadData()
void AdventureScene::SetTextNumber()
{
	if (GetStoryFlag()->GetFlag().at(3)
		&& GetStoryFlag()->GetFlag().at(4))
	{
		mTextNumber = 5;
		return;
	}


	if (GetStoryFlag()->GetSelectedKillFlag())
	{
		if (GetStoryFlag()->GetKillFlag())
		{
			mTextNumber = 3;
			return;
		}
		else
		{
			mTextNumber = 4;
			return;
		}
	}
	else if(GetStoryFlag()->GetReated())
	{
		mTextNumber = 2;
		return;
	}

	bool setText = false;
	int i = 0;
	while (!setText)
	{
		if (i >= GetStoryFlag()->GetSceneAmount())
		{
			std::cout << "Something wrong" << std::endl;
			mSceneManager->ChangeSceneType(SceneManager::SceneType::TITLE);
		}
		else if (!GetStoryFlag()->GetFlag().at(i))
		{
			mTextNumber = i;
			setText = true;
			return;
		}
		++i;
	}
}

//	Setter, but private, helper for only LoadData()
void AdventureScene::SetObject()
{
	LoadText(mTextNumber);

	Actor* temp = new Actor(mGame);
	temp->SetCentralPosition(Vector2(mGame->GetWindowCentralPos().x, mGame->GetWindowCentralPos().y + 100));


	switch (mTextNumber)
	{
	case 0:
		LoadActor(IMG_PLAYER, mDefaultPos, 2.0f, 0.0f, SDL_FLIP_VERTICAL);
		break;

	case 1:
		LoadActor(IMG_ENEMY1, mDefaultPos, 2.0f);
		LoadBG(IMG_ADVENTURE_BG1);
		break;

	case 2:
		LoadActor(IMG_PLAYER, Vector2((float)mGame->GetWindowWidth() - (float)mGame->GetWindowWidth() / 5.0f, (float)mGame->GetWindowHeight() / 3.0f), 2.0f,0.0f,SDL_FLIP_VERTICAL);
		LoadActor(IMG_ENEMY1, Vector2((float)mGame->GetWindowWidth() / 5.0f, (float)mGame->GetWindowHeight() / 3.0f), 2.0f, -80.0f);
		LoadBG(IMG_ADVENTURE_BG1);

		sm = new SelectSpriteComponent(temp);
		sm->SetTextures(IMG_KILLBRIGHT, IMG_KILL, IMG_NOTKILLBRIGHT, IMG_NOTKILL);
		sm->SetMenuVisualization(false);
		break;

	case 3:
		LoadBG(IMG_ADVENTURE_BG1);

		sm = new SelectSpriteComponent(temp);
		sm->SetTextures(IMG_REPEATBRIGHT, IMG_REPEAT, IMG_NOTREPEATBRIGHT, IMG_NOTREPEAT);
		sm->SetMenuVisualization(false);
		break;

	case 4:
		LoadActor(IMG_ENEMY1, mDefaultPos, 2.0f);
		LoadBG(IMG_ADVENTURE_BG1);

		sm = new SelectSpriteComponent(temp);
		sm->SetTextures(IMG_REPEATBRIGHT, IMG_REPEAT, IMG_NOTREPEATBRIGHT, IMG_NOTREPEAT);		sm->SetMenuVisualization(false);
		sm->SetMenuVisualization(false);
		break;

	case 5:
		LoadActor(IMG_ENEMY2, mDefaultPos, 2.0f);
		break;

	default:
		break;
	}
}

//	Setter, but private, helper for only LoadData()
void AdventureScene::LoadText(int i)
{
	std::ostringstream oss;
	oss << "Texts/text" << i << ".txt";

	mMessageWindow->LoadText(oss.str());
}

//	Setter, but private, helper for only UpdateScene()
void AdventureScene::SetNextScene()
{
	if (!mMessageWindow->GetOccupied())
	{
		SetFlag(mTextNumber);

		switch (mTextNumber)
		{
		case 0:
			mSceneManager->ChangeSceneType(SceneManager::SceneType::ADVENTURE);
			break;

		case 1:
			mSceneManager->ChangeSceneType(SceneManager::SceneType::BATTLE);
			break;

		case 2:
			if (!mDoneVisu) 
			{
				sm->SetMenuVisualization(true);
				mDoneVisu = true;
			}
			break;

		case 3:
			if (!mDoneVisu && !mGame->GetStoryFlag()->GetReated())
			{
				sm->SetMenuVisualization(true);
				mDoneVisu = true;
			}
			else if (mGame->GetStoryFlag()->GetFlag().at(4))
			{
				mSceneManager->ChangeSceneType(SceneManager::SceneType::ADVENTURE);
			}
			break;

		case 4:
			if (!mDoneVisu && !mGame->GetStoryFlag()->GetReated())
			{
				sm->SetMenuVisualization(true);
				mDoneVisu = true;
			}
			else if (mGame->GetStoryFlag()->GetFlag().at(3))
			{
				mSceneManager->ChangeSceneType(SceneManager::SceneType::ADVENTURE);
			}
			break;

		case 5:
			GetStoryFlag()->SetCleared();
			GetStoryFlag()->ResetFlags();
			mSceneManager->ChangeSceneType(SceneManager::SceneType::TITLE);
			break;

		default:
			break;
		}
	}
}
