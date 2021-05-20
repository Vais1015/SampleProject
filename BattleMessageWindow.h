#pragma once
#include "Actor.h"
#include "Math.h"
#include "SDL_ttf.h"
#include <string>
#include <queue>
#include <vector>

class BattleMessageWindow : public Actor
{
public:
    BattleMessageWindow(class Game* game, class BattleScene* scene);

    void UpdateActor(float deltaTime) override;
    void DisplayMessage(SDL_Renderer* renderer);

    void LoadText(std::string text);

    //  Getter
    bool GetRemainingText() const;

private:
    //  DisplayMessage‚Ìƒwƒ‹ƒp[ŠÖ”
    void SetTexture(SDL_Renderer* renderer,int i);

    struct TextTexture
    {
        SDL_Texture* textTexture;
        Vector2 position;
        int width;
        int height;
    };

    std::queue<std::string> mBattleTexts;
    std::vector<TextTexture> mTextTexture;

    float mInterval;
    SDL_Color mTextColor = { 255,255,255,255 };

    class BattleScene* mBattleScene;
};