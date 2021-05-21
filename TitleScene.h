#pragma once
#include "Scene.h"
#include <memory>

class TitleScene : public Scene
{
public:
	TitleScene(class Game*, class SceneMgr*);
	~TitleScene();

	void LoadData();

	void SceneInput(const uint8_t* keyState,SDL_Event* event) override;
	void UpdateScene(float deltaTime) override;
	void SceneOutput(SDL_Renderer* renderer) override;

private:
	class SelectMenu* mSM;
	class BGM* mBGM;
};