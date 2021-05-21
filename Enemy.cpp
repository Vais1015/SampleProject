#include "FilePath.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "BattleScene.h"
#include "BattleMessageWindow.h"
#include "SpriteComponent.h"
#include "BattleHP.h"
#include "SE.h"
#include "SDL.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sstream>

Enemy::Enemy(Game* game, BattleScene* battleScene, std::string enemyImg)
	:BattleCharacter(game, battleScene)
{
	std::cout << "Start Enemy" << std::endl;

	//	キャラの設定、左側に画像を反転せずに設置
	mPos = Vector2((float)(float)game->GetWindowWidth() / 5.0f,
		(float)game->GetWindowHeight() / 3.0f);

	this->SetCentralPosition(mPos);
	this->SetScale(mScale);

	mCharacterImage = new SpriteComponent(this, SDL_FLIP_NONE, mDrawOrder);
	mCharacterImage->SetTexture(game->SetTexture(enemyImg));

	//	ステータスの設定
	mStatus = { 550,300,65,70,30,SHOOT | FIRE | LIGHT,true, "Azel" };

	//	リカバリースピードの計算、バフなどでバトル中に変更はしない
	mRTRecoverySpd = (2.0f * (float)mStatus.Speed) / 100.0f;	//	1.1

	//	使える技
	mArts.push_back(Arts{ "STRIKE",1.0f,STRIKE,SE(SE_BATTLE_PUNCH) });
	mArts.push_back(Arts{ "WATER",1.0f,WATER,SE(SE_BATTLE_WATER) });
	mArts.push_back(Arts{ "DARK",2.0f,DARK,SE(SE_BATTLE_DARK) });

	//	体力表示
	mCharacterHP = new BattleHP(this, battleScene);
}

Enemy::~Enemy()
{
	std::cout << ":::Delete Enemy" << std::endl;
}

void Enemy::UpdateActor(float deltaTime)
{
	if (mStatus.Alive)
	{
		BattleCharacter::UpdateActor(deltaTime);

		if (mFromPreviousAttack == mCoolDown)
		{
			AttackPlayer(mBattleScene->GetPlayer());
		}

	}
	else
	{
		//	倒されたらSpriteを非表示にする
		SDL_SetTextureAlphaMod(mCharacterImage->GetTexture(), 0);

		mBattleScene->SetFinished(true);
	}
}

void Enemy::AttackPlayer(Player* target)
{
	Arts arts = SelectAttack();

	int offensivePower = mStatus.OffensivePower;
	int defensivePower = target->GetStatus().DefensivePower;
	int damage = mBattleScene->DamageCalculation(this, target, arts);

	//	攻撃したテキストをロード
	std::string str;
	str = mStatus.Name + " used " + arts.ArtsName + " to " + target->GetStatus().Name + " !!";
	mBattleScene->GetMessageWindow()->LoadText(str);

	arts.se.MakeSound();

	target->RecvDamage(damage);

	mHitWeakness = false;
	mFromPreviousAttack = 0;
}

//	ランダムで攻撃
Enemy::Arts Enemy::SelectAttack()
{
	std::srand((unsigned)std::time(NULL));

	int random = std::rand() % mArts.size();

	return mArts[random];
}


