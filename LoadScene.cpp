#include "Game.h"
#include "LoadScene.h"
#include <iostream>

LoadScene::LoadScene(Game* game, SceneManager* manager)
	:Scene(game,manager)
{
    std::cout << "Start LoadScene" << std::endl;

    mAlpha = 0;
}

LoadScene::~LoadScene()
{
    std::cout << ":::Delete LoadScene" << std::endl;
}

void LoadScene::UpdateScene(float deltaTime)
{
    mAlpha += (255.0f / 0.5f) * deltaTime;  //  0.5�b�ňÓ]

    if (mAlpha >= 255.0f)
    {
        SDL_Delay(1000);
        SetScene();
    }

    mTicksCount = SDL_GetTicks();
}

void LoadScene::SceneOutput(SDL_Renderer* renderer)
{
    Fadeout(renderer);
}

void LoadScene::Fadeout(SDL_Renderer* renderer)
{
    SDL_Rect rectangle;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    rectangle.x = 0;
    rectangle.y = 0;
    rectangle.w = mGame->GetWindowWidth();
    rectangle.h = mGame->GetWindowHeight();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, (Uint8)mAlpha);
    SDL_RenderFillRect(renderer, &rectangle);
    SDL_RenderPresent(renderer);
}

void LoadScene::SetScene()
{
    mGame->UnloadData();

    switch (mSceneManager->GetNextSceneType())
    {
    case SceneManager::SceneType::TITLE:
        mSceneManager->SetTitleScene();
        break;

    case SceneManager::SceneType::ADVENTURE:
        mSceneManager->SetAdventureScene();
        break;

    case SceneManager::SceneType::BATTLE:
        mSceneManager->SetBattleScene();
        break;

    case SceneManager::SceneType::LOAD:
        std::cout << "Load��ʂ���Load��ʂ֑J�ڂ��悤�Ƃ��Ă��܂�" << std::endl;
        break;

    default:
        break;
    }
}
