#include "BattleScene.h"
#include "Game.h"
#include "SceneManager.h"
#include "BattleMessageWindow.h"
#include "BGSpriteComponent.h"
#include "Player.h"
#include "ImgPath.h"
#include "Enemy.h"
#include <cmath>
#include <cstdlib>
#include <ctime>


BattleScene::BattleScene(Game* game,SceneManager* manager)
	:Scene(game,manager)
	,mFinished(false)
	,mFont(nullptr)
{
	std::cout << "Start BattleScene" << std::endl;

	mPlayer = new Player(game, this);
	mEnemy = new Enemy(game, this, IMG_ENEMY1);
	mMessageWindow = new BattleMessageWindow(game, this);

	LoadBG(IMG_BATTLE_BG1, -25.0f, IMG_BATTLE_BG2);
	LoadBG(IMG_BATTLE_BG3, -50.0f, IMG_BATTLE_BG3);

	mFont = TTF_OpenFont(FONT_ORANIENBAUM, 35);

	if (!mFont)
	{
		SDL_Log("font‚Ìæ“¾‚É¸”s‚µ‚Ü‚µ‚½F%s", TTF_GetError());
	}
}

BattleScene::~BattleScene()
{
	TTF_CloseFont(mFont);

	mGame->GetMemberSize();
	std::cout << ":::Delete BattleScene" << std::endl;
}

void BattleScene::SceneInput(const uint8_t* keyState)
{
	if (!mFinished)
	{
		Scene::SceneInput(keyState);
	}
}

void BattleScene::UpdateScene(float deltaTime)
{
	Scene::UpdateScene(deltaTime);

	if (mFinished)
	{
		mSceneManager->ChangeSceneType(SceneManager::SceneType::ADVENTURE);
	}
}

void BattleScene::SceneOutput(SDL_Renderer* renderer)
{
	mMessageWindow->DisplayMessage(renderer);

	Scene::SceneOutput(renderer);
}

//	UŒ‚—Í‚Æ–hŒä—Í‚©‚çƒ_ƒ[ƒW‚ğŒvZ
int BattleScene::DamageCalculation(BattleCharacter* attacker,BattleCharacter* defender,BattleCharacter::Arts arts)
{
	std::srand((unsigned)std::time(NULL));

	float random = (float)(std::rand() % 5 + 1) / 3;

	if (random < 0.7f)
		random = 0.7f;

	//	ƒ_ƒ[ƒWŒvZiUŒ‚—Í‚Ì2æ‚ğ–hŒä—Í‚ÅŠ„‚èA—”‚Æ‹Z‚ÌˆĞ—Í‚ğæZ
	double damage = (std::pow(attacker->GetStatus().OffensivePower, 2) / (double)defender->GetStatus().DefensivePower) 
		* (double)random * (double)arts.Power;

	//	ã“_‚É‚æ‚èæZ
	if (arts.Attribute & defender->GetStatus().Weakness)
	{
		damage *= 1.2;

		defender->SetHitWeakness(true);
	}

	return static_cast<int>(damage);
}

//	Getter
class Player* BattleScene::GetPlayer() const 
{
	return mPlayer; 
}

class Enemy* BattleScene::GetEnemy() const 
{
	return mEnemy; 
}

class BattleMessageWindow* BattleScene::GetMessageWindow() const 
{
	return mMessageWindow; 
}

TTF_Font* BattleScene::GetFont() const
{
	return mFont;
}

//	Setter
void BattleScene::SetFinished(bool finished)
{
	mFinished = finished; 
}

