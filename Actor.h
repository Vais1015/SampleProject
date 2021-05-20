#pragma once
#include "SDL.h"
#include "Math.h"
#include <vector>
#include <cstdint>

class Actor
{
public:
	enum class State {
		ACTIVE,
		PAUSED,
		DEAD
	};

	Actor(class Game*);
	virtual ~Actor();

	//Game�ŌĂяo�����X�V�֐�
	void Update(float deltaTime);			
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime) {};

	void ProcessInput(const uint8_t* keyState);
	virtual void ActorInput(const uint8_t* keyState) {};

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
	State mState;		//	�X�V�������̔���Ɏg�p
	Vector2 mPosition;	//	�ʒu
	float mScale;		//	�傫��
	float mRotation;	//	��]

	class Game* mGame;
	std::vector<class Component*> mComponents;
};