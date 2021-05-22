// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "FilePath.h"
#include "Game.h"
#include "SceneMgr.h"
#include "Actor.h"
#include "StoryFlag.h"
#include "SpriteComponent.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <algorithm>
#include <iostream>

Game::Game()
	:mWindow(nullptr)
	, mRenderer(nullptr)
	, mFont(nullptr)
	, mIsRunning(true)
	, mUpdatingActors(false)
	, mDeltaTime(0)
	, mTicksCount(0)
	, mInputTime(0)
	, mPressed(false)
	, mSceneManager(nullptr)
	, mStoryFlag(nullptr)
{

}

bool Game::Initialize()
{
	//SDLを初期化
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		SDL_Log("初期化に失敗しました：%s", SDL_GetError());
		return false;
	}

	//	Windowの作成
	mWindow = SDL_CreateWindow("Sample Program", 100, 50, mWindowWidth, mWindowHeight, 0);
	if (!mWindow)
	{
		SDL_Log("Windowsの作成に失敗しました：%s", SDL_GetError());
		return false;
	}

	//	Rendererの作成
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) 
	{
		SDL_Log("Rendererの作成に失敗しました：%s", SDL_GetError());
		return false;
	}

	//	IMGの初期化
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("sdl_imageの初期化に失敗しました：%s", SDL_GetError());
		return false;
	}

	//	Soundの初期化
	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024))
	{
		SDL_Log("Audioの初期化に失敗しました:%s", SDL_GetError());
	}

	//	Fontの初期化
	if (TTF_Init() != 0) {
		SDL_Log("ttfの初期化に失敗しました：%s", TTF_GetError());
	}

	mFont = TTF_OpenFont(FONT_HANAMIN, mFontSize);
	if (!mFont)
	{
		SDL_Log("fontの取得に失敗しました：%s", TTF_GetError());
	}

	LoadData();

	mTicksCount = SDL_GetTicks();

	return true;
}

void Game::Runloop()
{
	while (mIsRunning) 
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::Shutdown() 
{
	delete mSceneManager;
	delete mStoryFlag;

	UnloadData();

	TTF_CloseFont(mFont);
	TTF_Quit();

	Mix_CloseAudio();

	IMG_Quit();

	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::LoadData()
{
	//	入れ替え厳禁（TitleSceneでStoryFlagを使用するため）
	mStoryFlag = new StoryFlag();
	mSceneManager = new SceneMgr(this);
}

void Game::UnloadData()
{
	while(!mActors.empty())
	{
		delete mActors.back();
	}

	// Destroy textures
	for (auto i : mTextures)
		SDL_DestroyTexture(i.second);

	mTextures.clear();

	std::cout << ":::Unload Data" << std::endl;
}

void Game::ProcessInput()
{
	SDL_Event event;
	

	while (SDL_PollEvent(&event)) 
	{
		switch (event.type)
		{
		//	Windowのバツボタンで停止
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	mUpdatingActors = true;
	//Sceneごとにインプットを処理
	mSceneManager->SceneInput(keyState, &event);
	mUpdatingActors = false;
}

void Game::UpdateGame() 
{
	//フレーム待機
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	mDeltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	if (mDeltaTime > 0.05f) {
		mDeltaTime = 0.05f;
	}

	mTicksCount = SDL_GetTicks();

	mSceneManager->UpdateScene(mDeltaTime);
}

void Game:: UpdateActors(float deltaTime) 
{
	// すべてのactorsを更新
	mUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	// pendingActorsを更新できるようにactorsに追加
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// 使わないactorsを無効化して削除
	std::vector<Actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->GetState() == Actor::State::DEAD)
		{
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput() 
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
 
	for (auto sprite : mSprites)
		sprite->Draw(mRenderer);

	mSceneManager->SceneOutput(mRenderer);

	SDL_RenderPresent(mRenderer);
}

void Game::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// pendingActorsの確認
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// actorsの確認
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}


//	Getter
class SceneMgr* Game::GetSceneManager() const 
{
	return mSceneManager; 
}

class StoryFlag* Game::GetStoryFlag() const
{
	return mStoryFlag; 
}

int Game::GetWindowWidth() const 
{
	return mWindowWidth; 
}

int Game:: GetWindowHeight() const 
{
	return mWindowHeight; 
}

Vector2 Game::GetScreenSize() const 
{
	return Vector2((float)mWindowWidth, (float)mWindowHeight); 
}

Vector2 Game::GetWindowCentralPos() const 
{
	return Vector2((float)mWindowWidth / 2.0f, (float)mWindowHeight / 2.0f); 
}

Uint32 Game::GetTicksCount() const 
{
	return mTicksCount; 
}

Uint32 Game::GetInputTime() const
{
	return mInputTime;
}

bool Game::GetPressed() const
{
	return mPressed;
}

std::vector<Actor*> Game::GetActors() const 
{
	return mActors; 
}

std::vector<SpriteComponent*> Game::GetSprites() const 
{
	return mSprites; 
}

TTF_Font* Game::GetFont() const 
{
	return mFont; 
}


//	Setter
SDL_Texture* Game::SetTexture(std::string fileName)
{
	SDL_Texture* texture = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		texture = iter->second;
	}
	else
	{
		SDL_Surface* surface;

		surface = IMG_Load(fileName.c_str());

		if (!surface)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);

		if (!texture)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), texture);
	}
	return texture;
}

void Game::SetIsRunning(bool isRunning) 
{
	mIsRunning = isRunning; 
}

void Game::SetUpdatingActors(bool updatingActors) 
{
	mUpdatingActors = updatingActors; 
}

void Game::SetInputTime()
{
	mInputTime = SDL_GetTicks();
}

void Game::SetPressedFalse()
{
	mPressed = false;
}
