#include "BattleHP.h"
#include "Actor.h"
#include "Game.h"
#include "BattleCharacter.h"
#include "BattleScene.h"
#include "SDL_ttf.h"
#include <sstream>

BattleHP::BattleHP(BattleCharacter* chara,BattleScene* scene)
	:SpriteComponent(chara)
	,mBattleScene(scene)
	,mBattleCharacter(chara)
{
	
}

void BattleHP::Draw(SDL_Renderer* renderer)
{
	std::ostringstream oss;
	oss << mBattleCharacter->GetStatus().HP;

	SDL_Surface* surface = TTF_RenderUTF8_Blended(mBattleScene->GetFont(), oss.str().c_str(), SDL_Color{ 255,255,255,255 });
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect r;
	SDL_QueryTexture(texture, nullptr, nullptr, &r.w, &r.h);
	r.x = static_cast<int>(mOwner->GetCentralPosition().x - (mTexWidth / 2.0f));
	r.y = static_cast<int>(mOwner->GetCentralPosition().y * 2.0f);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderCopy(renderer, texture, nullptr, &r);

	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}