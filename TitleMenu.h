#pragma once
#include "Actor.h"

class TitleMenu :public Actor
{
public:
	TitleMenu(class Game*);
	~TitleMenu();

	void ActorInput(const uint8_t* keyState);

private:
	class TitleMenuSpriteComponent* mTitleMenuSC;
};