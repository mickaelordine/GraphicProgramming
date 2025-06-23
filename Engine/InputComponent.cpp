#include "InputComponent.h"
#include "Actor.h"

//defines for keyboard
#define VK_LEFT           0x25
#define VK_RIGHT          0x27

InputComponent::InputComponent(class Actor* owner)
	:MoveComponent(owner)
	, m_RightKey(0)
	, m_LeftKey(0)
{

}

void InputComponent::ProcessInput(InputClass* keyState)
{
	// Calculate angular speed for MoveComponent
	float horzSpeed = 0.0f;
	if (keyState->IsKeyDown(VK_RIGHT) && m_Owner->GetPosition().x < 60.0f)
	{
		horzSpeed += m_MaxHorzSpeed;
	}
	if (keyState->IsKeyDown(VK_LEFT) && m_Owner->GetPosition().x > -60.0f)
	{
		horzSpeed -= m_MaxHorzSpeed;
	}
	SetHorizontalSpeed(horzSpeed);
}
