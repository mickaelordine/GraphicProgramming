#include "SquareComponent.h"
#include "Actor.h"

SquareComponent::SquareComponent(Actor* owner)
	:Component(owner)
	, m_Width(0.0f)
	, m_Height(0.0f)
{
	
}

const Vector2& SquareComponent::GetCenter() const{
	return m_Owner->GetPosition();
}
