#pragma once
#include "Component.h"
#include "MoveComponent.h"


class InputComponent : public MoveComponent
{
public:
	// Lower update order to update first
	InputComponent(class Actor* owner);

	void ProcessInput(InputClass* keyState) override;

	// Getters/setters for private variables
	float GetMaxHorz() const { return m_MaxHorzSpeed; }
	int GetRightKey() const { return m_RightKey; }
	int GetLeftKey() const { return m_LeftKey; }

	void SetMaxHorzSpeed(float speed) { m_MaxHorzSpeed = speed; }
	void SetRightKey(int key) { m_RightKey = key; }
	void SetLeftKey(int key) { m_LeftKey = key; }
private:
	float m_MaxHorzSpeed = 25.0f;

	// Keys for Right/Left movement
	int m_RightKey;
	int m_LeftKey;
};
