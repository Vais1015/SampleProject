// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Game.h"
#include "Actor.h"
#include "Component.h"
#include <algorithm>
#include <iostream>

Actor::Actor(Game* game)
	:mState(State::ACTIVE)
	, mPosition(Vector2::Zero)
	, mScale(1.0f)
	, mRotation(0.0f)
	, mGame(game)
{
	game->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Actor::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

void Actor::ProcessInput(const uint8_t* keyState, SDL_Event* event)
{
	if (mState == State::ACTIVE)
	{
		// First process input for components
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState, event);
		}

		ActorInput(keyState, event);
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == State::ACTIVE)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

//	Getter
Game* Actor::GetGame() const
{
	return mGame; 
}

Vector2 Actor::GetCentralPosition() const 
{
	return mPosition; 
}

float Actor::GetScale() const 
{
	return mScale; 
}

float Actor::GetRotation() const 
{
	return mRotation; 
}

Actor::State Actor::GetState() const
{
	return mState; 
}


//	Setter
void Actor::SetCentralPosition(const Vector2& pos) 
{
	mPosition = pos; 
}

void Actor::SetScale(float scale) 
{
	mScale = scale; 
}

void Actor::SetRotation(float rotation)
{
	mRotation = rotation; 
}

void Actor::SetState(State state) 
{
	mState = state; 
}



