#include "InputComponent.h"
#include "Actor.h"

InputComponent::InputComponent(class Actor* owner)
	:MoveComponent(owner)
	, m_RightKey(0)
	, m_LeftKey(0)
{

}

void InputComponent::ProcessInput(const bool* keyState)
{
	// Calculate angular speed for MoveComponent
	float angularSpeed = 0.0f;
	if (keyState[m_RightKey])
	{
		angularSpeed += m_MaxHorzSpeed;
	}
	if (keyState[m_LeftKey])
	{
		angularSpeed -= m_MaxHorzSpeed;
	}
	SetMaxHorzSpeed(angularSpeed);
}
