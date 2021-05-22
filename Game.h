// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include "Math.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

class Game
{
public:
	Game();

	bool Initialize();
	void Runloop();
	void Shutdown();

	void LoadData();
	void UnloadData();

	void AddActor(class Actor*);
	void RemoveActor(class Actor*);

	void AddSprite(class SpriteComponent*);
	void RemoveSprite(class SpriteComponent*);

	//Runloopのヘルパー関数
	void ProcessInput();
	void UpdateGame();
	void UpdateActors(float deltaTime);
	void GenerateOutput();

	//	Getter
	class SceneMgr* GetSceneManager() const;
	class StoryFlag* GetStoryFlag() const;

	int GetWindowWidth() const;
	int GetWindowHeight() const;
	Vector2 GetScreenSize() const;
	Vector2 GetWindowCentralPos() const;

	Uint32 GetInputTime() const;
	Uint32 GetTicksCount() const;
	bool GetPressed() const;

	std::vector<Actor*> GetActors() const;
	std::vector<SpriteComponent*> GetSprites() const;

	TTF_Font* GetFont() const;

	//	Setter
	SDL_Texture* SetTexture(std::string fileName);
	void SetIsRunning(bool isRunning);
	void SetUpdatingActors(bool updatingActors);
	void SetInputTime();
	void SetPressedFalse();

private:
	bool mPressed;

	class SceneMgr* mSceneManager;
	class StoryFlag* mStoryFlag;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	TTF_Font* mFont;
	int mFontSize = 30;

	//	ロード済みのtextureをまとめた配列
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<class SpriteComponent*> mSprites;

	//	Actorをまとめた配列
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	bool mUpdatingActors;

	int mWindowWidth = 1280;
	int mWindowHeight = 720;

	Uint32 mInputTime;	//	キー入力の時間
	Uint32 mTicksCount;
	float mDeltaTime;	//単位秒
	bool mIsRunning;
};
