#include "FilePath.h"
#include "BattleMenuSpriteComponent.h"
#include "Game.h"
#include "BattleScene.h"
#include "Actor.h"
#include "Player.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

BattleMenu::BattleMenu(Game* game, BattleScene* scene)
	:SelectMenu(game)
{
	mBMSC = new BattleMenuSpriteComponent(this, scene);
}

BattleMenuSpriteComponent::BattleMenuSpriteComponent(SelectMenu* owner,BattleScene* battle)
	:SelectSpriteComponent(owner)
	,mBattleScene(battle)
{

}

void BattleMenuSpriteComponent::Draw(SDL_Renderer* renderer)
{
	if (!mBattleScene->GetFinished())
	{
		float time = mBattleScene->GetPlayer()->GetCoolDown() - mBattleScene->GetPlayer()->GetFromPreviousAttack();
		//	攻撃できないとき、リキャストタイムを表示
		if (time != 0)
		{
			SetMenuVisualization(false);

			std::ostringstream oss;
			oss << std::fixed << std::setprecision(2) << time;

			SDL_Surface* surface = TTF_RenderUTF8_Blended(mBattleScene->GetFont(), oss.str().c_str(), SDL_Color{ 255,255,255,255 });
			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

			//	テクスチャの位置と大きさ
			SDL_Rect r;

			SDL_QueryTexture(texture, nullptr, nullptr, &r.w, &r.h);
			r.x = static_cast<int>(mOwner->GetGame()->GetWindowCentralPos().x - (r.w / 2.0f));
			r.y = static_cast<int>(mOwner->GetGame()->GetWindowCentralPos().y - 60);

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderCopy(renderer, texture, nullptr, &r);

			SDL_FreeSurface(surface);
			SDL_DestroyTexture(texture);
		}
		//	攻撃できるときは選択肢を表示
		else
		{
			SetMenuVisualization(true);
			SelectSpriteComponent::Draw(renderer);
		}
	}
	else if (mBattleScene->GetFinished())
	{
		SetMenuVisualization(false);
	}
}


