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

	void UpdateActor(float deltaTime) override;
	void ActorInput(const uint8_t* keyState) override;

	void AttackEnemy(class Enemy* target,Arts arts);

private:
	Vector2 mPos;
	float mScale = 2.0f;
	int mDrawOrder = 120;

	std::vector<Arts> mArts;

	//	inputがあってからのインターバル
	float mInterval = 0.5f; //単位秒
	Uint32 mInputTime;
};