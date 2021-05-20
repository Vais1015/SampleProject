#include "Player.h"
#include "Enemy.h"
#include "Game.h"
#include "BattleScene.h"
#include "SceneManager.h"
#include "BattleMessageWindow.h"
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

	mCharacterImage = new SpriteComponent(this, SDL_FLIP_VERTICAL, mDrawOrder);
	mCharacterImage->SetTexture(game->SetTexture(mPlayerImg));

	//	�X�e�[�^�X�̐ݒ�
	mStatus = { 2000,300,80,65,65, STRIKE | WINDOW | DARK , "You" };

	//	���J�o���[�X�s�[�h�̌v�Z�A�o�t�ȂǂŃo�g�����ɕύX�͂��Ȃ�
	mRTRecoverySpd = (2.0f * (float)mStatus.Speed) / 100.0f;	//	1.3

	//	�g����Z
	mArts.push_back(Arts{ "STRIKE",1.0f,STRIKE });
	mArts.push_back(Arts{ "GUN",1.0f,SHOOT });
	mArts.push_back(Arts{ "LIGHT",1.0f,LIGHT });

	//	BattleMenu�̐ݒ�A�ʒu�͐ݒ�ς�
	mBM = new BattleMenuSpriteComponent(this, battleScene);

	//	�̗͂�\������SpriteComponent
	mCharacterHP = new BattleHP(this,battleScene);
}

void Player::UpdateActor(float deltaTime)
{

	if (mCondition == Condition::ALIVE)
	{
		BattleCharacter::UpdateActor(deltaTime);

		if (mFromPreviousAttack == mCoolDown)
		{
			mBM->SetCanInput(true);
		}
	}
	else if (mCondition == Condition::DEAD)
	{
		mBM->SetCanInput(false);

		//	�|���ꂽ��Sprite���\���ɂ���
		SDL_SetTextureAlphaMod(mCharacterImage->GetTexture(), 0);

		mBattleScene->SetFinished(true);
	}
}

void Player::ActorInput(const uint8_t* keyState)
{
	if (mFromPreviousAttack == mCoolDown && keyState[SDL_SCANCODE_SPACE])
	{
		switch (mBM->GetSpriteType())
		{
		case BattleMenuSpriteComponent::SpriteType::STRIKE:
			AttackEnemy(mBattleScene->GetEnemy(), mArts[0]);
			break;

		case BattleMenuSpriteComponent::SpriteType::SHOOT:
			AttackEnemy(mBattleScene->GetEnemy(), mArts[1]);
			break;
				
		default:
			break;
		}
	}
}

void Player::AttackEnemy(class Enemy* target,Arts arts)
{
	mBM->SetCanInput(false);

	int offensivePower = mStatus.OffensivePower;

	int defensivePower = target->GetStatus().DefensivePower;

	int damage = mBattleScene->DamageCalculation(this, target, arts);

	//	�U���������Ƃ��E�B���h�E�ɕ\��
	std::string str;
	str = mStatus.Name + " used " + arts.ArtsName + " to " + target->GetStatus().Name+" !!";
	mBattleScene->GetMessageWindow()->LoadText(str);

	target->RecvDamage(damage);

	mHitWeakness = false;
	mFromPreviousAttack = 0;
}

