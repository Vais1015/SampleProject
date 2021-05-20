#include "Game.h"
#include "BattleMessageWindow.h"
#include "SpriteComponent.h"
#include "BattleScene.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include <fstream>
#include <assert.h>

BattleMessageWindow::BattleMessageWindow(Game* game, BattleScene* scene)
    :Actor(game)
    ,mBattleScene(scene)
    ,mInterval(0)
{
    SetCentralPosition(Vector2((float)game->GetWindowWidth() / 2.0f, (float)game->GetWindowHeight() - ((float)game->GetWindowHeight() / 5.0f)));
}

void BattleMessageWindow::UpdateActor(float deltaTime)
{
    mInterval += deltaTime;
}

//  テキストを表示
void BattleMessageWindow::DisplayMessage(SDL_Renderer* renderer)
{
    //  1.5秒表示したテキストを削除
    if (mInterval > 1.5f && !mTextTexture.empty())
    {
        for (auto i : mTextTexture)
        {
            SDL_DestroyTexture(i.textTexture);
        }
        mTextTexture.clear();
    }

    //  テクスチャがあるなら表示
    if (!mTextTexture.empty())
    {
        for (auto i : mTextTexture)
        {
            SDL_Rect r;
            r.x = (int)i.position.x;
            r.y = (int)i.position.y;
            r.w = i.width;
            r.h = i.height;
            
            SDL_RenderCopy(renderer, i.textTexture, nullptr, &r);
        }
    }

    //  テキストがある場合、最高３つのテキストをテクスチャに変換
    if (!mBattleTexts.empty() && mTextTexture.empty())
    {
        if (mBattleTexts.size() > 2)
        {
            for (int i = 0; i < 3; ++i)
            {
                SetTexture(renderer, i);
            }
        }
        else
        {
            for (unsigned int i = 0; i < mBattleTexts.size(); ++i)
            {
                SetTexture(renderer, i);
            }
        }

        mInterval = 0;
    }
}

void BattleMessageWindow::LoadText(std::string text)
{
    mBattleTexts.push(text);
}

void BattleMessageWindow::SetTexture(SDL_Renderer* renderer,int i)
{
    TextTexture temp;

    //  読み込んだテキストをすべてテクスチャに変換して削除
    //  テキスト、フォント、カラー、Gameで設定したサイズを設定
    SDL_Surface* surface = TTF_RenderUTF8_Blended(mBattleScene->GetFont(), mBattleTexts.front().c_str(), mTextColor);
    temp.textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_QueryTexture(temp.textTexture, nullptr, nullptr, &temp.width, &temp.height);

    //  TextをActorの位置をもとに中央揃え
    //  連続でセットした場合はテクスチャを下にずらす
    temp.position.x = GetCentralPosition().x - (temp.width / 2.0f);
    temp.position.y = GetCentralPosition().y - 35.0f + (35.0f * i);

    mTextTexture.push_back(temp);
    mBattleTexts.pop();

    SDL_FreeSurface(surface);
}

//  Getter
bool BattleMessageWindow::GetRemainingText() const
{
    if (!mBattleTexts.empty() && !mTextTexture.empty())
    {
        return true;
    }
    else if(mBattleTexts.empty() && mTextTexture.empty())
    {
        return false;
    }
    else
    {
        return true;
    }
}