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

//  �e�L�X�g��\��
void BattleMessageWindow::DisplayMessage(SDL_Renderer* renderer)
{
    //  1.5�b�\�������e�L�X�g���폜
    if (mInterval > 1.5f && !mTextTexture.empty())
    {
        for (auto i : mTextTexture)
        {
            SDL_DestroyTexture(i.textTexture);
        }
        mTextTexture.clear();
    }

    //  �e�N�X�`��������Ȃ�\��
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

    //  �e�L�X�g������ꍇ�A�ō��R�̃e�L�X�g���e�N�X�`���ɕϊ�
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

    //  �ǂݍ��񂾃e�L�X�g�����ׂăe�N�X�`���ɕϊ����č폜
    //  �e�L�X�g�A�t�H���g�A�J���[�AGame�Őݒ肵���T�C�Y��ݒ�
    SDL_Surface* surface = TTF_RenderUTF8_Blended(mBattleScene->GetFont(), mBattleTexts.front().c_str(), mTextColor);
    temp.textTexture = SDL_CreateTextureFromSurface(renderer, surface);
    
    SDL_QueryTexture(temp.textTexture, nullptr, nullptr, &temp.width, &temp.height);

    //  Text��Actor�̈ʒu�����Ƃɒ�������
    //  �A���ŃZ�b�g�����ꍇ�̓e�N�X�`�������ɂ��炷
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