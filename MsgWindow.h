#pragma once
#include "Actor.h"
#include "Math.h"
#include "SDL_ttf.h"
#include <string>

class MsgWindow :public Actor
{
public:
    MsgWindow(class Game*);
    ~MsgWindow();

    void LoadText(std::string textFile);
    void DisplayMessageWindow(SDL_Renderer*);
    void ActorInput(const uint8_t* keyState, SDL_Event* event) override;

    //  Getter;
    bool GetOccupied() const;

private:
    float mWindowScale = 1.2f;
    int mWindowDrawOrder = 150;

    bool mOcuupied;

    class SpriteComponent* mWindowSC;
    std::vector<std::string> mText;
    Vector2 mTextPos;
    SDL_Color mTextColor = { 255,255,255,255 };

    float mInterval = 0.5f; //’PˆÊ•b
};