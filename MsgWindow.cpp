#include "FilePath.h"
#include "Game.h"
#include "MsgWindow.h"
#include "SpriteComponent.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include <fstream>

MsgWindow::MsgWindow(Game* game)
    :Actor(game)
    , mOcuupied(false)
    ,mWindowSC(nullptr)
{
    std::cout << "Start MsgWindow" << std::endl;

    SetCentralPosition(Vector2((float)game->GetWindowWidth() / 2.0f,
        (float)game->GetWindowHeight() - ((float)game->GetWindowHeight() / 5.0f)));

    mWindowSC = new SpriteComponent(this);
    mWindowSC->SetTexture(game->SetTexture(IMG_WINDOW));
}

MsgWindow::~MsgWindow()
{
    std::cout << ":::Delete MsgWindow" << std::endl;
}

//  読み込んだテキストを１行ずつ表示
void MsgWindow::DisplayMessageWindow(SDL_Renderer* renderer)
{
    if (!mText.empty())
    {
        //テキストの表示
        SDL_Surface* surface = TTF_RenderUTF8_Blended(GetGame()->GetFont(), mText[0].c_str(), mTextColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        int iw, ih;
        SDL_QueryTexture(texture, nullptr, nullptr, &iw, &ih);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        //  Window画像の中心を基準に計算
        mTextPos.x = GetCentralPosition().x - 30 * 11;
        mTextPos.y = GetCentralPosition().y - 30;

        SDL_Rect pasteRect = SDL_Rect{ (int)mTextPos.x,(int)mTextPos.y , iw,ih };
        SDL_RenderCopy(renderer, texture, nullptr, &pasteRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);

        mOcuupied = true;
    }
    else
    {
        mOcuupied = false;
        SDL_SetTextureAlphaMod(mWindowSC->GetTexture(), 0);
    }
}

void MsgWindow::ActorInput(const uint8_t* keyState, SDL_Event* event)
{
    float interval = (SDL_GetTicks() - GetGame()->GetInputTime()) / 1000.0f;

    //Spaceキーで表示しているテキストを削除し進める
    if (!mText.empty()
        && event->key.keysym.scancode==SDL_SCANCODE_SPACE)
    {
        mText.erase(mText.begin());
    }
}

//テキストをテキストファイルからロード
void MsgWindow::LoadText(std::string textFile) 
{
    std::ifstream ifs(textFile);
    if (!ifs)
    {
        std::cout << "error :ファイルを開けませんでした" << std::endl;
    }

    std::string temp;
    while (getline(ifs, temp))
    {
        mText.push_back(temp);
    }

    ifs.close();

    mOcuupied = true;
}

//  Getter
bool MsgWindow::GetOccupied() const 
{
    return mOcuupied;
}

