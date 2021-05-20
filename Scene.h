#pragma once
#include "Math.h"
#include "SDL.h"
#include <vector>
#include <string>
#include <memory>

class Scene
{
public:
	Scene(class Game*, class SceneManager*);
	virtual ~Scene();

	virtual void SceneInput(const uint8_t* keyState);
	virtual void UpdateScene(float deltaTime);
	virtual void SceneOutput(SDL_Renderer* renderer);

	//	Setter
	void LoadActor(std::string imgPath, Vector2 pos, float scale, float rotation = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void LoadBG( std::string img1, float scrollSpeed = 0.0f, std::string img2 = "");

protected:
	class Game* mGame;
	class SceneManager* mSceneManager;

	float mAlpha;
};
