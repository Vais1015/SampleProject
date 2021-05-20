#pragma once
#include "SpriteComponent.h"

class BattleHP : public SpriteComponent
{
public:
	BattleHP(class BattleCharacter* chara, class BattleScene* scene);

	void Draw(SDL_Renderer* renderer) override;

private:
	class BattleCharacter* mBattleCharacter;
	class BattleScene* mBattleScene;
};