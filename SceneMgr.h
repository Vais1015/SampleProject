#pragma once
#include "Game.h"
#include "Scene.h"
#include <memory>

class SceneMgr
{
public:
	enum class SceneType
	{
		TITLE,
		ADVENTURE,
		BATTLE,
		LOAD
	};

	SceneMgr(class Game*);
	~SceneMgr();

	void SceneInput(const uint8_t* keyState, SDL_Event* event);
	void UpdateScene(float deltaTime);
	void SceneOutput(SDL_Renderer* renderer);
	
	void ChangeSceneType(SceneType nextSceneType);
	void DeleteOldScene();

	//	Getter
	SceneType GetCurrSceneType() const;
	SceneType GetNextSceneType() const;

	// Setter
	void SetTitleScene();
	void SetAdventureScene();
	void SetBattleScene();


	void SetCurrSceneType(SceneType st);
	void SetNextSceneType(SceneType st);

private:
	std::vector<std::unique_ptr<Scene>> mScenes;
	SceneType mCurrSceneType;
	SceneType mNextSceneType;

	class Game* mGame;
};