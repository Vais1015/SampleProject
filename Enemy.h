#pragma once
#include "BattleCharacter.h"
#include <string>
#include <vector>

class Enemy : public BattleCharacter  
{
public:
	Enemy(class Game*, class BattleScene*, std::string enemyImg);
	~Enemy();

	void UpdateActor(float deltaTime) override;

	void AttackPlayer(class Player* target);

private:
	//	AttackPlayer()‚Ìƒwƒ‹ƒp[
	Arts SelectAttack();
};