#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int temUpdateOrder)
	:mOwner(owner)
	, mUpdateOrder(mUpdateOrder)
{
	mOwner->AddComponent(this);		// Add to actor's vector of components
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}
