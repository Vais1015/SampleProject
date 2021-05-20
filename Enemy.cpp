#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "BattleScene.h"
#include "BattleMessageWindow.h"
#include "SpriteComponent.h"
#include "BattleHP.h"
#include "SDL.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>

Enemy::Enemy(Game* game, BattleScene* battleScene,std::string enemyImg)
	:BattleCharacter(game, battleScene)
{
	std::cout << "Start Enemy" << std::endl;

	//	�L�����̐ݒ�A�����ɉ摜�𔽓]�����ɐݒu
	mPos = Vector2((float)(float)game->GetWindowWidth() / 5.0f,
		(float)game->GetWindowHeight() / 3.0f);

	this->SetCentralPosition(mPos);
	this->SetScale(mScale);

	mCharacterImage = new SpriteComponent(this, SDL_FLIP_NONE, mDrawOrder);
	mCharacterImage->SetTexture(game->SetTexture(enemyImg));

	//	�X�e�[�^�X�̐ݒ�
	mStatus = { 550,300,65,70,30,SHOOT | FIRE | LIGHT, "Azel" };

	//	���J�o���[�X�s�[�h�̌v�Z�A�o�t�ȂǂŃo�g�����ɕύX�͂��Ȃ�
	mRTRecoverySpd = (2.0f * (float)mStatus.Speed) / 100.0f;	//	1.1

	//	�g����Z
	mArts.push_back(Arts{ "STRIKE",1.0f,STRIKE });
	mArts.push_back(Arts{ "WATER",1.0f,WATER });
	mArts.push_back(Arts{ "DARK",2.0f,DARK });

	//	�̗͕\��
	mCharacterHP = new BattleHP(this,battleScene);
}

Enemy::~Enemy()
{
	std::cout << ":::Delete Enemy" << std::endl;
}

void Enemy::UpdateActor(float deltaTime)
{
	if (mCondition == Condition::ALIVE)
	{
		BattleCharacter::UpdateActor(deltaTime);

		if (mFromPreviousAttack == mCoolDown)
		{
			AttackPlayer(mBattleScene->GetPlayer());
		}

	}
	else if (mCondition == Condition::DEAD)
	{
		//	�|���ꂽ��Sprite���\���ɂ���
		SDL_SetTextureAlphaMod(mCharacterImage->GetTexture(), 0);

		mBattleScene->SetFinished(true);
	}
}

void Enemy::AttackPlayer(Player* target)
{
	int offensivePower = mStatus.OffensivePower;
	Arts arts = SelectAttack();

	int defensivePower = target->GetStatus().DefensivePower;

	int damage = mBattleScene->DamageCalculation(this, target, arts);

	//	�U�������e�L�X�g�����[�h
	std::string str;
	str = mStatus.Name + " used " + arts.ArtsName + " to " + target->GetStatus().Name + " !!";
	mBattleScene->GetMessageWindow()->LoadText(str);

	target->RecvDamage(damage);

	mHitWeakness = false;
	mFromPreviousAttack = 0;
}

//	�����_���ōU��
Enemy::Arts Enemy::SelectAttack()
{
	std::srand((unsigned)std::time(NULL));

	int random = std::rand() % mArts.size();

	return mArts[random];
}


