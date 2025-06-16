#pragma once
#include "Component.h"

class MoveComponent : public Component
{
public:
	// Lower update order to update first
	MoveComponent(class Actor* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float GetHorizontalSpeed() const { return m_HorizzontalSpeed; }
	float GetForwardSpeed() const { return m_ForwardSpeed; }

	void SetHorizontalSpeed(float speed) { m_HorizzontalSpeed = speed; }
	void SetForwardSpeed(float speed) { m_ForwardSpeed = speed; }

private:
	float m_HorizzontalSpeed;
	float m_ForwardSpeed;
};

