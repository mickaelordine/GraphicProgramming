#include "SquareComponent.h"
#include "Actor.h"

SquareComponent::SquareComponent(Actor* owner)
	:Component(owner)
	, m_Width(0.0f)
	, m_Height(0.0f)
{
	
}

const Vector2& SquareComponent::GetCenter() const{
	if(m_Owner->GetState() != 1 && m_Owner->GetState() != 2)
		return m_Owner->GetPosition(); //accessviolation here
}
