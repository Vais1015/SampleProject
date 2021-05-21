#pragma once
#include "SDL.h"
#include <cstdint>

class Component
{
public:
	
	Component(class Actor*, int temUpdateOrder = 100);	// (the lower the update order, the earlier the component updates)
	virtual ~Component();

	virtual void ProcessInput(const uint8_t* keyState, SDL_Event* event) {}
	virtual void Update(float deltaTime);

	int GetUpdateOrder() const { return mUpdateOrder; }

protected:
	class Actor* mOwner;
	int mUpdateOrder;
};
