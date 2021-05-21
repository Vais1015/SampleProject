#pragma once
#include "BattleCharacter.h"
#include "BattleMenuSpriteComponent.h"
#include "SDL.h"
#include <string>
#include <vector>

class Player : public BattleCharacter
{
public:
	Player(class Game*, class BattleScene*);
	~Player();

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState, SDL_Event* event) override;

	void AttackEnemy(class Enemy* target,Arts arts);

private:
	//	inputがあってからのインターバル
	float mInterval = 0.5f; //単位秒
	Uint32 mInputTime;
};