#pragma once
#include "Scene.h"

class AdventureScene :public Scene
{
public:
	AdventureScene(class Game*, class SceneManager*);
	~AdventureScene();

	void SceneInput(const uint8_t* keyState) override;
	void UpdateScene(float deltaTime) override;
	void SceneOutput(SDL_Renderer* renderer) override;

	//	Getter
	class StoryFlag* GetStoryFlag() const;

	//	Setter
	void SetFlag(int textNumber);

private:
	class MessageWindow* mMessageWindow;
	int mTextNumber;

	class SelectMenu* sm;
	bool mDoneVisu;

	
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