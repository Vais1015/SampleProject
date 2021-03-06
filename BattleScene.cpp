#include "FilePath.h"
#include "Game.h"
#include "SceneMgr.h"
#include "BattleScene.h"
#include "Player.h"
#include "Enemy.h"
#include "BattleMessageWindow.h"
#include "BGSpriteComponent.h"
#include "BattleMenuSpriteComponent.h"
#include "BGM.h"
#include <cmath>
#include <cstdlib>
#include <ctime>


BattleScene::BattleScene(Game* game,SceneMgr* manager)
	:Scene(game,manager)
	,mFinished(false)
	,mFont(nullptr)
{
	std::cout << "Start BattleScene" << std::endl;

	mPlayer = new Player(game, this);
	mEnemy = new Enemy(game, this, IMG_ENEMY1);
	mMessageWindow = new BattleMsgWindow(game, this);

	Actor* temp = new Actor(game);
	temp->SetCentralPosition(Vector2(mGame->GetWindowCentralPos().x, mGame->GetWindowCentralPos().y - 50));
	mBM = new BattleMenuSpriteComponent(temp,this);
	mBM->SetTextures(IMG_STRIKEBRIGHT, IMG_STRIKE, IMG_SHOOTBRIGHT, IMG_SHOOT);
	mBM->SetMenuVisualization(false);

	LoadBG(IMG_BATTLE_BG1, -25.0f, IMG_BATTLE_BG2);
	LoadBG(IMG_BATTLE_BG3, -50.0f, IMG_BATTLE_BG3);

	mFont = TTF_OpenFont(FONT_ORANIENBAUM, 35);

	if (!mFont)
	{
		SDL_Log("fontの取得に失敗しました：%s", TTF_GetError());
	}

	mBGM = new BGM(new Actor(game));
	mBGM->StartBGM(BGM_BATTLE, 30);
}

BattleScene::~BattleScene()
{
	TTF_CloseFont(mFont);

	std::cout << ":::Delete BattleScene" << std::endl;
}

void BattleScene::SceneInput(const uint8_t* keyState, SDL_Event* event)
{
	if (!mFinished)
	{
		Scene::SceneInput(keyState, event);
	}
}

void BattleScene::UpdateScene(float deltaTime)
{
	Scene::UpdateScene(deltaTime);

	if (mFinished)
	{
		mBM->SetMenuVisualization(false);

		if (!mMessageWindow->GetRemainingText())
		{
			mBGM->StopBGM();
			mSceneManager->ChangeSceneType(SceneMgr::SceneType::ADVENTURE);
		}
	}
}

void BattleScene::SceneOutput(SDL_Renderer* renderer)
{
	mMessageWindow->DisplayMessage(renderer);

	Scene::SceneOutput(renderer);
}

//	攻撃力と防御力からダメージを計算
int BattleScene::DamageCalculation(BattleCharacter* attacker,BattleCharacter* defender,BattleCharacter::Arts arts)
{
	std::srand((unsigned)std::time(NULL));

	float random = (float)(std::rand() % 5 + 1) / 3;

	if (random < 0.9f)
		random = 0.9f;

	//	ダメージ計算（攻撃力の2乗を防御力で割り、乱数と技の威力を乗算
	double damage = (std::pow(attacker->GetStatus().OffensivePower, 2) / (double)defender->GetStatus().DefensivePower) 
		* (double)random * (double)arts.Power;

	//	弱点により乗算
	if (arts.Attribute & defender->GetStatus().Weakness)
	{
		damage *= 1.2;

		defender->SetHitWeakness(true);
		defender->SetDisplayedHitWeakness(false);
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

class BattleMsgWindow* BattleScene::GetMessageWindow() const 
{
	return mMessageWindow; 
}

class BattleMenuSpriteComponent* BattleScene::GetSelectMenu() const
{
	return mBM;
}

TTF_Font* BattleScene::GetFont() const
{
	return mFont;
}

bool BattleScene::GetFinished() const
{
	return mFinished;
}

//	Setter
void BattleScene::SetFinished(bool finished)
{
	mFinished = finished; 
}

