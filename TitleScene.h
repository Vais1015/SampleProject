#pragma once
#include "Scene.h"
#include <memory>

class TitleScene : public Scene
{
public:
	TitleScene(class Game*, class SceneManager*);
	~TitleScene();

	void LoadData();

	void SceneInput(const uint8_t* keyState) override;
	void UpdateScene(float deltaTime) override;
	void SceneOutput(SDL_Renderer* renderer) override;

private:
	class SelectSpriteComponent* mSM;
	class BGMComponent* mBGM;
};