#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(class Actor* owner, int updateOrder)
	:Component(owner, updateOrder)
	, m_HorizzontalSpeed(0.0f)
	, m_ForwardSpeed(0.0f)
{

}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(m_HorizzontalSpeed))
	{
		float rot = m_Owner->GetRotation();
		rot += m_HorizzontalSpeed * deltaTime;
		m_Owner->SetRotation(rot);
	}

	if (!Math::NearZero(m_ForwardSpeed))
	{
		Vector2 pos = m_Owner->GetPosition();
		pos += m_Owner->GetForward() * m_ForwardSpeed * deltaTime; //check here

		// Screen Bouncing (for balls)
		if (pos.x < -70.0f) { m_HorizzontalSpeed = -m_HorizzontalSpeed; }
		else if (pos.x > 70.0f) { m_HorizzontalSpeed = -m_HorizzontalSpeed; }
		if (pos.y < -40.0f) { m_ForwardSpeed = -m_ForwardSpeed; }
		else if (pos.y > 40.0f) { m_ForwardSpeed = -m_ForwardSpeed; }

		m_Owner->SetPosition(pos);
	}
}
