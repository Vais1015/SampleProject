#pragma once
#include "Scene.h"

class AdventureScene :public Scene
{
public:
	AdventureScene(class Game*, class SceneMgr*);
	~AdventureScene();

	void SceneInput(const uint8_t* keyState, SDL_Event* event) override;
	void UpdateScene(float deltaTime) override;
	void SceneOutput(SDL_Renderer* renderer) override;

	//	Getter
	class StoryFlag* GetStoryFlag() const;

	//	Setter
	void SetFlag(int textNumber);

private:
	class MsgWindow* mMessageWindow;
	int mTextNumber;

	class SelectMenu* mSM;
	bool mDoneVisu;

	class BGM* mBGM;

	
	//	キャラクターの基本位置
	Vector2 mDefaultPos = Vector2(mGame->GetWindowCentralPos().x, mGame->GetWindowCentralPos().y - 100);
	
	//	コンストラクタで使用
	void LoadData();
	//	Helper for LoadData()
	void SetTextNumber();
	void SetObject();
	void LoadText(int i);
	//	Helper for UpdateScene()
	void SetNextScene();
};