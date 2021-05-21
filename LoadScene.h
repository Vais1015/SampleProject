#pragma once
#include "Scene.h"
#include "SceneMgr.h"

class LoadScene : public Scene
{
public:

	LoadScene(class Game*, class SceneMgr*);
	~LoadScene();

	void SceneInput(const uint8_t* keyState, SDL_Event* event) override {};
	void UpdateScene(float deltaTime) override;
	void SceneOutput(SDL_Renderer* renderer) override;
	void Fadeout(SDL_Renderer* renderer);

	void SetScene();

private:
	Uint32 mTicksCount = 0;
};