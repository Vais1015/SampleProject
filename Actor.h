#pragma once
#include "SDL.h"
#include "Math.h"
#include <vector>
#include <cstdint>

class Actor
{
public:
	enum class State 
	{
		ACTIVE,
		PAUSED,
		DEAD
	};

	Actor(class Game*);
	virtual ~Actor();

	//Gameで呼び出される更新関数
	void Update(float deltaTime);			
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime) {};

	void ProcessInput(const uint8_t* keyState, SDL_Event* event);
	virtual void ActorInput(const uint8_t* keyState, SDL_Event* event) {};

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	//	Getter
	class Game* GetGame() const;
	Vector2 GetCentralPosition() const;
	float GetScale() const;
	float GetRotation() const;
	State GetState() const;

	//	Setter
	void SetCentralPosition(const Vector2& pos);
	void SetScale(float scale);
	void SetRotation(float rotation);
	void SetState(State state);

private:
	State mState;		//	更新時処理の判定に使用
	Vector2 mPosition;	//	位置
	float mScale;		//	大きさ
	float mRotation;	//	回転

	class Game* mGame;
	std::vector<class Component*> mComponents;
};