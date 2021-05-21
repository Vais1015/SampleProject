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
	//	input�������Ă���̃C���^�[�o��
	float mInterval = 0.5f; //�P�ʕb
	Uint32 mInputTime;
};