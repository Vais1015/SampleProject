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

	//	input�������Ă���̃C���^�[�o��
	float mInterval = 0.5f; //�P�ʕb
	Uint32 mInputTime;
};