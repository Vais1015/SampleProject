#include "Game.h"
#include "SceneMgr.h"
#include "TitleScene.h"
#include "AdventureScene.h"
#include "BattleScene.h"
#include "LoadScene.h"
#include  <iostream>

SceneMgr::SceneMgr(Game* game)
    :mGame(game)
    , mCurrSceneType(SceneType::TITLE)
    , mNextSceneType(SceneType::LOAD)
{
    std::cout << "Start SceneMgr" << std::endl;

    mScenes.emplace_back(std::make_unique<TitleScene>(game,this));
}

SceneMgr::~SceneMgr()
{
    std::cout << ":::Delete SceneMgr" << std::endl;
}

void SceneMgr::SceneInput(const uint8_t* keyState, SDL_Event* event) 
{
    mScenes.front()->SceneInput(keyState, event); 
}

void SceneMgr::UpdateScene(float deltaTime) 
{
    mScenes.front()->UpdateScene(deltaTime); 
}

void SceneMgr::SceneOutput(SDL_Renderer* renderer)
{
    mScenes.front()->SceneOutput(renderer); 
}

void SceneMgr::ChangeSceneType(SceneType nextSceneType)
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

void SceneMgr::DeleteOldScene()
{
    mScenes.pop_back();
}

//	Getter
SceneMgr::SceneType SceneMgr::GetCurrSceneType() const 
{
    return mCurrSceneType; 
}

SceneMgr::SceneType SceneMgr::GetNextSceneType() const 
{
    return mNextSceneType; 
}

//  Setter
void SceneMgr::SetTitleScene()
{
    DeleteOldScene();
    mScenes.insert(mScenes.begin(),std::make_unique<TitleScene>(mGame,this));
    SetCurrSceneType(SceneType::TITLE);
    SetNextSceneType(SceneType::LOAD);
}

void SceneMgr::SetAdventureScene() 
{
    DeleteOldScene();
    mScenes.insert(mScenes.begin(),std::make_unique<AdventureScene>(mGame,this));
    SetCurrSceneType(SceneType::ADVENTURE);
    SetNextSceneType(SceneType::LOAD);
}

void SceneMgr::SetBattleScene()
{
    DeleteOldScene();
    mScenes.insert(mScenes.begin(), std::make_unique<BattleScene>(mGame, this));
    SetCurrSceneType(SceneType::BATTLE);
    SetNextSceneType(SceneType::LOAD);
}

void SceneMgr::SetCurrSceneType(SceneType st)
{
    mCurrSceneType = st;
}

void SceneMgr::SetNextSceneType(SceneType st) 
{
    mNextSceneType = st;
}
