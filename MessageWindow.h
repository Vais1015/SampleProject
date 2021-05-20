#pragma once
#include "Actor.h"
#include "Math.h"
#include "SDL_ttf.h"
#include <string>

class MessageWindow :public Actor
{
public:
    MessageWindow(class Game*);
    ~MessageWindow();

    void LoadText(std::string textFile);
    void DisplayMessageWindow(SDL_Renderer*);
    void ActorInput(const uint8_t* keyState) override;

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

    std::string mWindowPath = "Assets/MessageWindowAdventure.png";
};