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

	//Runloop�̃w���p�[�֐�
	void ProcessInput();
	void UpdateGame();
	void UpdateActors(float deltaTime);
	void GenerateOutput();

	//	Getter
	class SceneManager* GetSceneManager() const;
	class StoryFlag* GetStoryFlag() const;

	int GetWindowWidth() const;
	int GetWindowHeight() const;
	Vector2 GetScreenSize() const;
	Vector2 GetWindowCentralPos() const;

	Uint32 GetInputTime() const;
	Uint32 GetTicksCount() const;

	std::vector<Actor*> GetActors() const;
	std::vector<SpriteComponent*> GetSprites() const;

	TTF_Font* GetFont() const;

	//	Setter
	SDL_Texture* SetTexture(std::string fileName);
	void SetIsRunning(bool isRunning);
	void SetUpdatingActors(bool updatingActors);
	void SetInputTime();

	//	Debug
	void GetMemberSize() {
		std::cout << std::endl;
		std::cout << "mTextures : " << mTextures.size() << std::endl;
		std::cout << "mSprites : " << mSprites.size() << std::endl;
		std::cout << "mActors : " << mActors.size() << std::endl;
		std::cout << std::endl;
	}

private:
	class SceneManager* mSceneManager;
	class StoryFlag* mStoryFlag;

	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

	TTF_Font* mFont;
	int mFontSize = 30;

	//	���[�h�ς݂�texture���܂Ƃ߂��z��
	std::unordered_map<std::string, SDL_Texture*> mTextures;

	std::vector<class SpriteComponent*> mSprites;

	//	Actor���܂Ƃ߂��z��
	std::vector<class Actor*> mActors;
	std::vector<class Actor*> mPendingActors;
	bool mUpdatingActors;

	int mWindowWidth = 1280;
	int mWindowHeight = 720;

	Uint32 mInputTime;	//	�L�[���͂̎���
	Uint32 mTicksCount;
	float mDeltaTime;	//�P�ʕb
	bool mIsRunning;
};
