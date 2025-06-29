#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)
	:m_Owner(owner)
	, m_UpdateOrder(updateOrder)
{
	// Add to actor's vector of components
	m_Owner->AddComponent(this);
}

Component::~Component()
{
	m_Owner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}
