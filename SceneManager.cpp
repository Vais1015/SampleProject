#include "Game.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "AdventureScene.h"
#include "BattleScene.h"
#include "LoadScene.h"
#include  <iostream>

SceneManager::SceneManager(Game* game)
    :mGame(game)
    , mCurrSceneType(SceneType::TITLE)
    , mNextSceneType(SceneType::LOAD)
{
    std::cout << "Start SceneManager" << std::endl;

    mScenes.emplace_back(std::make_unique<TitleScene>(game,this));
}

SceneManager::~SceneManager()
{
    std::cout << ":::Delete SceneManager" << std::endl;
}

void SceneManager::SceneInput(const uint8_t* keyState) 
{
    mScenes.front()->SceneInput(keyState); 
}

void SceneManager::UpdateScene(float deltaTime) 
{
    mScenes.front()->UpdateScene(deltaTime); 
}

void SceneManager::SceneOutput(SDL_Renderer* renderer)
{
    mScenes.front()->SceneOutput(renderer); 
}

void SceneManager::ChangeSceneType(SceneType nextSceneType)
{
    if (nextSceneType == SceneType::LOAD)
    {
        std::cout << "Load‰æ–Ê‚Ö‚Ì‘JˆÚ‚Í”F‚ß‚ç‚ê‚Ü‚¹‚ñ" << std::endl;
        mScenes.insert(mScenes.begin(), std::make_unique<LoadScene>(mGame, this));
        mCurrSceneType = SceneType::LOAD;
        mNextSceneType = SceneType::TITLE;
        return;
    }

    mScenes.insert(mScenes.begin(),std::make_unique<LoadScene>(mGame,this));
    mCurrSceneType = SceneType::LOAD;
    mNextSceneType = nextSceneType;
}

void SceneManager::DeleteOldScene()
{
    mScenes.pop_back();
}

//	Getter
SceneManager::SceneType SceneManager::GetCurrSceneType() const 
{
    return mCurrSceneType; 
}

SceneManager::SceneType SceneManager::GetNextSceneType() const 
{
    return mNextSceneType; 
}

//  Setter
void SceneManager::SetTitleScene()
{
    DeleteOldScene();
    mScenes.insert(mScenes.begin(),std::make_unique<TitleScene>(mGame,this));
    SetCurrSceneType(SceneType::TITLE);
    SetNextSceneType(SceneType::LOAD);
}

void SceneManager::SetAdventureScene() 
{
    DeleteOldScene();
    mScenes.insert(mScenes.begin(),std::make_unique<AdventureScene>(mGame,this));
    SetCurrSceneType(SceneType::ADVENTURE);
    SetNextSceneType(SceneType::LOAD);
}

void SceneManager::SetBattleScene()
{
    DeleteOldScene();
    mScenes.insert(mScenes.begin(), std::make_unique<BattleScene>(mGame, this));
    SetCurrSceneType(SceneType::BATTLE);
    SetNextSceneType(SceneType::LOAD);
}

void SceneManager::SetCurrSceneType(SceneType st)
{
    mCurrSceneType = st;
}

void SceneManager::SetNextSceneType(SceneType st) 
{
    mNextSceneType = st;
}
