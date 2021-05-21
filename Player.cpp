#include "FilePath.h"
#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "BattleScene.h"
#include "SceneMgr.h"
#include "BattleMessageWindow.h"
#include "SE.h"
#include "SpriteComponent.h"
#include "BattleHP.h"
#include <iostream>
#include <sstream>

Player::Player(Game* game, BattleScene* battleScene)
	:BattleCharacter(game, battleScene)
	, mInputTime(0)
{
	//	�L�����̐ݒ�A�E���ɉ摜�𔽓]���Đݒu
	mPos = Vector2((float)game->GetWindowWidth() - (float)game->GetWindowWidth() / 5.0f,
		(float)game->GetWindowHeight() / 3.0f);

	SetCentralPosition(mPos);
	SetScale(mScale);

	mCharacterImg = new SpriteComponent(this, SDL_FLIP_VERTICAL, mDrawOrder);
	mCharacterImg->SetTexture(game->SetTexture(IMG_PLAYER));

	//	�X�e�[�^�X�̐ݒ�
	mStatus = { 2000,300,80,65,65, STRIKE | WINDOW | DARK ,true, "You" };

	//	���J�o���[�X�s�[�h�̌v�Z�A�o�t�ȂǂŃo�g�����ɕύX�͂��Ȃ�
	mRTRecoverySpd = (2.0f * (float)mStatus.Speed) / 100.0f;	//	1.3

	//	�g����Z
	mArts.push_back(Arts{ "STRIKE",1.0f,STRIKE,new SE(SE_BATTLE_SWORD) });
	mArts.push_back(Arts{ "GUN",1.0f,SHOOT,new SE(SE_BATTLE_GUN) });

	//	�̗͂�\������SpriteComponent
	mCharacterHP = new BattleHP(this,battleScene);
}

Player::~Player()
{

}

void Player::UpdateActor(float deltaTime)
{

	if (mStatus.Alive)
	{
		BattleCharacter::UpdateActor(deltaTime);
	}
	else
	{
		//	�|���ꂽ��Sprite���\���ɂ���
		SDL_SetTextureAlphaMod(mCharacterImg->GetTexture(), 0);

		mBattleScene->SetFinished(true);
	}
}

void Player::ActorInput(const uint8_t* keyState, SDL_Event* event)
{
	if (mFromAttack == mCoolDown
		&& event->key.keysym.scancode == SDL_SCANCODE_SPACE)
	{
		if (mBattleScene->GetSelectMenu()->GetIsTop())
		{
			AttackEnemy(mBattleScene->GetEnemy(), mArts[0]);
		}
		else
		{
			AttackEnemy(mBattleScene->GetEnemy(), mArts[1]);
		}
	}
}

void Player::AttackEnemy(class Enemy* target,Arts arts)
{
	int offensivePower = mStatus.OffensivePower;
	int defensivePower = target->GetStatus().DefensivePower;
	int damage = mBattleScene->DamageCalculation(this, target, arts);

	//	�U���������Ƃ��E�B���h�E�ɕ\��
	std::string str;
	str = mStatus.Name + " used " + arts.ArtsName + " to " + target->GetStatus().Name+" !!";
	mBattleScene->GetMessageWindow()->LoadText(str);

	arts.se->MakeSound();

	target->RecvDamage(damage);

	mHitWeakness = false;
	mFromAttack = 0;
}

