#pragma once
#include "SelectMenu.h"
#include "Math.h"
#include <vector>
#include <string>

class BattleMenu : public SelectMenu
{
public:
	BattleMenu(class Game* game, class BattleScene* scene);

private:
	class BattleMenuSpriteComponent* mBMSC;
};

class BattleMenuSpriteComponent :public SelectSpriteComponent
{
public:
	BattleMenuSpriteComponent(class SelectMenu* owner, class BattleScene* battle);

	void Draw(SDL_Renderer* renderer) override;

private:
	class BattleScene* mBattleScene;
};