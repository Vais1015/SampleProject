#include "BattleScene.h"
#include "BattleCharacter.h"
#include "SpriteComponent.h"
#include "Math.h"
#include "SDL.h"
#include "BattleMessageWindow.h"
#include "SE.h"
#include "FilePath.h"
#include <string>
#include <iostream>
#include <sstream>

BattleCharacter::BattleCharacter(Game* game, BattleScene* battleScene)
	:Actor(game)
	,mBattleScene(battleScene)
	, mCharacterImg(nullptr)
	,mCharacterHP(nullptr)
	, mStatus{ 0,0,0,0,0,0,true, "" }
	, mFromAttack(0)
	, mRTRecoverySpd(0)
	, mHitWeakness(false)
	,mDisplayedHitWeaknessMsg(false)
{

}

BattleCharacter::~BattleCharacter()
{
	for (auto i : mArts)
	{
		delete i.se;
	}
}

void BattleCharacter::UpdateActor(float deltaTime)
{
	if (!mBattleScene->GetFinished())
	{
		//	�O�̍U������̃��L���X�g�^�C�����v�Z
		if (!mHitWeakness)
		{
			mFromAttack += (deltaTime * mRTRecoverySpd);
		}
		else
		{
			mFromAttack += (deltaTime * mRTRecoverySpd * mSlowDown);
		}

		if (mFromAttack > mCoolDown)
		{

			mFromAttack = mCoolDown;
		}
	}
}

void BattleCharacter::RecvDamage(int damage)
{
	// BattleMessageWindow�Ƀ_���[�W�Ǝc��̗͂������e�L�X�g�����[�h
	std::ostringstream oss;
	std::string str;

	if (mHitWeakness && !mDisplayedHitWeaknessMsg)
	{
		str = "Hit Weakness !!";
		mBattleScene->GetMessageWindow()->LoadText(str);
		mDisplayedHitWeaknessMsg = true;
	}

	oss << damage;
	str = oss.str() + " Damage !!";

	mBattleScene->GetMessageWindow()->LoadText(str);

	mStatus.HP -= damage;

	if (mStatus.HP <= 0)
	{
		mStatus.HP = 0;
		mStatus.Alive = false;

		//	BattleMessageWindow��Player���͐s�����e�L�X�g�����[�h
		str = mStatus.Name + " exhausted.";
		mBattleScene->GetMessageWindow()->LoadText(str);
	}
}

//	Getter
BattleCharacter::Status BattleCharacter::GetStatus() const 
{
	return mStatus; 
}

float BattleCharacter::GetCoolDown() const
{
	return mCoolDown;
}

float BattleCharacter::GetFromPreviousAttack() const
{
	return mFromAttack;
}

//	Setter
void BattleCharacter::SetHitWeakness(bool hit)
{
	mHitWeakness = hit;
}

void BattleCharacter::SetDisplayedHitWeakness(bool displayed)
{
	mDisplayedHitWeaknessMsg = displayed;
}
