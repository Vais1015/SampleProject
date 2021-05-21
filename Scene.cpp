#include "Game.h"
#include "Scene.h"
#include "Actor.h"
#include "BGSpriteComponent.h"
#include "Math.h"
#include <iostream>

Scene::Scene(Game* game, SceneMgr* sceneManager)
	:mGame(game)
	,mSceneManager(sceneManager)
	,mAlpha(255.0f)
{
	std::cout << "Start Scene" << std::endl ;
}

Scene::~Scene()
{
	std::cout << ":::Delete Scene" << std::endl << std::endl;
}

void Scene::SceneInput(const uint8_t* keyState, SDL_Event* event)
{
	for (auto actor : mGame->GetActors())
	{
		actor->ProcessInput(keyState,event);
	}
}

void Scene::UpdateScene(float deltaTime)
{
	mAlpha -= (255.0f / 0.5f) * deltaTime;  //  0.5•b‚Å–¾“]

	if (mAlpha <=0.0f)
	{
		mAlpha = 0.0f;

		mGame->UpdateActors(deltaTime);
	}
}

void Scene::SceneOutput(SDL_Renderer* renderer)
{
	if (mAlpha > 0)
	{
		SDL_Rect rectangle;
		SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

		rectangle.x = 0;
		rectangle.y = 0;
		rectangle.w = mGame->GetWindowWidth();
		rectangle.h = mGame->GetWindowHeight();

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, (Uint8)mAlpha);
		SDL_RenderFillRect(renderer, &rectangle);
		SDL_RenderPresent(renderer);
	}
}

//	Setter
void Scene::LoadActor(std::string imgPath, Vector2 pos, float scale, float rotation, SDL_RendererFlip flip)
{
	Actor* actor = new Actor(mGame);
	actor->SetCentralPosition(pos);
	actor->SetScale(scale);
	actor->SetRotation(rotation);

	SpriteComponent* sc = new SpriteComponent(actor, flip);
	sc->SetTexture(mGame->SetTexture(imgPath));
}

void Scene::LoadBG(std::string img1, float scrollSpeed, std::string img2)
{
	std::vector<std::string> str;

	if (img2 == "")
	{
		str.push_back(img1);
	}
	else
	{
		str.push_back(img1);
		str.push_back(img2);
	}

	Actor* temp = new Actor(mGame);
	temp->SetCentralPosition(mGame->GetWindowCentralPos());

	BGSpriteComponent* bg = new BGSpriteComponent(temp, str, scrollSpeed);
}

