#pragma once
#include "Scene.h"
#include "BattleCharacter.h"
#include "SDL_ttf.h"

class BattleScene :public Scene
{
public:
	BattleScene(class Game*, class SceneMgr*);
	~BattleScene();

	void SceneInput(const uint8_t* keyState, SDL_Event* event) override;
	void UpdateScene(float deltaTime) override;
	void SceneOutput(SDL_Renderer* renderer) override;

	int DamageCalculation(BattleCharacter* attacker,BattleCharacter* defender,BattleCharacter::Arts arts);

	//	Getter
	class Player* GetPlayer() const;
	class Enemy* GetEnemy() const;
	class BattleMsgWindow* GetMessageWindow() const;
	class BattleMenu* GetSelectMenu() const;
	TTF_Font* GetFont() const;
	bool GetFinished() const;

	//	Setter
	void SetFinished(bool finished);



private:
	class Player* mPlayer;
	class Enemy* mEnemy;
	class BattleMsgWindow* mMessageWindow;
	class BattleMenu* mBM;
	class BGM* mBGM;

	bool mFinished;
	TTF_Font* mFont;
};