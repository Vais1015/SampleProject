#include "FilePath.h"
#include "Game.h"
#include "StoryFlag.h"
#include "SceneMgr.h"
#include "AdventureScene.h"
#include "MsgWindow.h"
#include "BGSpriteComponent.h"
#include "SelectMenu.h"
#include "BGM.h"
#include <sstream>
#include <iostream>

AdventureScene::AdventureScene(class Game* game, SceneMgr* manager)
	:Scene(game, manager)
	, mTextNumber(0)
	, mSM(nullptr)
	, mDoneVisu(false)
{
	std::cout << "Start AdventureScene" << std::endl;

	LoadData();
}

AdventureScene::~AdventureScene()
{
	std::cout << ":::Delete AdventureScene" << std::endl;
}

void AdventureScene::LoadData()
{
	mMessageWindow = new MsgWindow(mGame);

	SetTextNumber();
	SetObject();
}


void AdventureScene::SceneInput(const uint8_t* keyState, SDL_Event* event)
{
	Scene::SceneInput(keyState,event);

	if (mTextNumber == 2)
	{
		if (mSM->GetCanInput()
			&& event->key.keysym.scancode == SDL_SCANCODE_SPACE)
		{
			if (mSM->GetIsTop())
			{
				mBGM->StopBGM();
				mGame->GetStoryFlag()->SetKillFlag(true);
				mGame->GetSceneManager()->ChangeSceneType(SceneMgr::SceneType::ADVENTURE);
			}
			else
			{
				mBGM->StopBGM();
				mGame->GetStoryFlag()->SetKillFlag(false);
				mGame->GetSceneManager()->ChangeSceneType(SceneMgr::SceneType::ADVENTURE);
			}
		}
	}

	if (mTextNumber == 3 || mTextNumber == 4)
	{
		if (mSM->GetCanInput()
			&& event->key.keysym.scancode == SDL_SCANCODE_SPACE)
		{
			if (mSM->GetIsTop())
			{
				mBGM->StopBGM();
				GetStoryFlag()->SetSelectedKillFlag(false);
				GetStoryFlag()->SetReated();
				mGame->GetSceneManager()->ChangeSceneType(SceneMgr::SceneType::ADVENTURE);
			}
			else
			{
				mBGM->StopBGM();
				mGame->GetSceneManager()->ChangeSceneType(SceneMgr::SceneType::TITLE);
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
			mSceneManager->ChangeSceneType(SceneMgr::SceneType::TITLE);
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

	//	SelectMenu—p
	mSM = new SelectMenu(mGame);
	mSM->SetCentralPosition(Vector2(mGame->GetWindowCentralPos().x, mGame->GetWindowCentralPos().y + 150));

	//	BGM
	mBGM = new BGM(new Actor(mGame));
	if (mTextNumber != 5)
	{
		mBGM->StartBGM(BGM_ADVENTURE, 45);
	}
	else
	{
		mBGM->StartBGM(BGM_ADVENTURE2, 45);
	}

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

		mSM->SetTextures(IMG_KILLBRIGHT, IMG_KILL, IMG_NOTKILLBRIGHT, IMG_NOTKILL);
		mSM->SetMenuVisualization(false);
		break;

	case 3:
		LoadActor(IMG_PLAYER, mDefaultPos, 2.0f, 0, SDL_FLIP_VERTICAL);
		LoadBG(IMG_ADVENTURE_BG1);

		mSM->SetTextures(IMG_REPEATBRIGHT, IMG_REPEAT, IMG_NOTREPEATBRIGHT, IMG_NOTREPEAT);
		mSM->SetMenuVisualization(false);
		break;

	case 4:
		LoadActor(IMG_ENEMY1, mDefaultPos, 2.0f);
		LoadBG(IMG_ADVENTURE_BG1);

		mSM->SetTextures(IMG_REPEATBRIGHT, IMG_REPEAT, IMG_NOTREPEATBRIGHT, IMG_NOTREPEAT);	
		mSM->SetMenuVisualization(false);
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
			mBGM->StopBGM();
			mSceneManager->ChangeSceneType(SceneMgr::SceneType::ADVENTURE);
			break;

		case 1:
			mBGM->StopBGM();
			mSceneManager->ChangeSceneType(SceneMgr::SceneType::BATTLE);
			break;

		case 2:
			if (!mDoneVisu) 
			{
				mSM->SetMenuVisualization(true);
				mDoneVisu = true;
			}
			break;

		case 3:
			if (!mDoneVisu && !mGame->GetStoryFlag()->GetReated())
			{
				mSM->SetMenuVisualization(true);
				mDoneVisu = true;
			}
			else if (mGame->GetStoryFlag()->GetFlag().at(4))
			{
				mSceneManager->ChangeSceneType(SceneMgr::SceneType::ADVENTURE);
			}
			break;

		case 4:
			if (!mDoneVisu && !mGame->GetStoryFlag()->GetReated())
			{
				mSM->SetMenuVisualization(true);
				mDoneVisu = true;
			}
			else if (mGame->GetStoryFlag()->GetFlag().at(3))
			{
				mSceneManager->ChangeSceneType(SceneMgr::SceneType::ADVENTURE);
			}
			break;

		case 5:
			mBGM->StopBGM();
			GetStoryFlag()->SetCleared();
			GetStoryFlag()->ResetFlags();
			mSceneManager->ChangeSceneType(SceneMgr::SceneType::TITLE);
			break;

		default:
			break;
		}
	}
}
