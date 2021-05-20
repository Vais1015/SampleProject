#include "Game.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Actor.h"
#include "TitleMenu.h"
#include "TitleMenuSpriteComponent.h"
#include "BGSpriteComponent.h"
#include <iostream>

TitleMenu::TitleMenu(Game* game)
	:Actor(game)
{
	std::cout << "Start TitleMenu" << std::endl;

	mTitleMenuSC = new TitleMenuSpriteComponent(this);
}

TitleMenu::~TitleMenu()
{
	std::cout << ":::Delete TitleMenu" << std::endl;
}

void TitleMenu::ActorInput(const uint8_t* keyState)
{
	if (keyState[SDL_SCANCODE_SPACE])
	{
		if (mTitleMenuSC->GetSpriteType() == TitleMenuSpriteComponent::SpriteType::START)
		{
			GetGame()->GetSceneManager()->ChangeSceneType(SceneManager::SceneType::ADVENTURE);
		}
		else if (mTitleMenuSC->GetSpriteType() == TitleMenuSpriteComponent::SpriteType::END)
		{
			GetGame()->SetIsRunning(false);
		}

		GetGame()->SetInputTime();
	}
}
