#include "FilePath.h"
#include "Game.h"
#include "MessageWindow.h"
#include "SpriteComponent.h"
#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include <fstream>

MessageWindow::MessageWindow(Game* game)
    :Actor(game)
    , mOcuupied(false)
    ,mWindowSC(nullptr)
{
    std::cout << "Start MessageWindow" << std::endl;

    SetCentralPosition(Vector2((float)game->GetWindowWidth() / 2.0f,
        (float)game->GetWindowHeight() - ((float)game->GetWindowHeight() / 5.0f)));

    mWindowSC = new SpriteComponent(this);
    mWindowSC->SetTexture(game->SetTexture(IMG_WINDOW));
}

MessageWindow::~MessageWindow()
{
    std::cout << ":::Delete MessageWindow" << std::endl;
}

//  �ǂݍ��񂾃e�L�X�g���P�s���\��
void MessageWindow::DisplayMessageWindow(SDL_Renderer* renderer)
{
    if (!mText.empty())
    {
        //�e�L�X�g�̕\��
        SDL_Surface* surface = TTF_RenderUTF8_Blended(GetGame()->GetFont(), mText[0].c_str(), mTextColor);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        int iw, ih;
        SDL_QueryTexture(texture, nullptr, nullptr, &iw, &ih);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

        //  Window�摜�̒��S����Ɍv�Z
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

void MessageWindow::ActorInput(const uint8_t* keyState)
{
    float interval = (SDL_GetTicks() - GetGame()->GetInputTime()) / 1000.0f;

    //Space�L�[�ŕ\�����Ă���e�L�X�g���폜���i�߂�
    if (!mText.empty()
        && keyState[SDL_SCANCODE_SPACE]
        && interval > mInterval)
    {
        mText.erase(mText.begin());
        GetGame()->SetInputTime();
    }
}

//�e�L�X�g���e�L�X�g�t�@�C�����烍�[�h
void MessageWindow::LoadText(std::string textFile) 
{
    std::ifstream ifs(textFile);
    if (!ifs)
    {
        std::cout << "error :�t�@�C�����J���܂���ł���" << std::endl;
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
bool MessageWindow::GetOccupied() const 
{
    return mOcuupied;
}

