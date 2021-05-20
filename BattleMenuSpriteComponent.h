#pragma once
#include "SelectMenu.h"
#include "Math.h"
#include <vector>
#include <string>

class BattleMenuSpriteComponent :public SelectSpriteComponent
{
public:
	BattleMenuSpriteComponent(class Actor* owner, class BattleScene* battle);

	void Draw(SDL_Renderer* renderer) override;

private:
	class BattleScene* mBattleScene;
};