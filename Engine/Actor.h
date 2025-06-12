#pragma once
#include <vector>
#include "Math.h"
#include <cstdint>

class Actor
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const uint8_t* keyState);
	// Any actor-specific input code (overridable)
	virtual void ActorInput(const uint8_t* keyState);

	// Getters/setters
	const Vector2& GetPosition() const { return m_Position; }
	void SetPosition(const Vector2& pos) { m_Position = pos; m_RecomputeWorldTransform = true; }
	float GetScale() const { return m_Scale; }
	void SetScale(float scale) { m_Scale = scale;  m_RecomputeWorldTransform = true; }
	float GetRotation() const { return m_Rotation; }
	void SetRotation(float rotation) { m_Rotation = rotation;  m_RecomputeWorldTransform = true; }

	void ComputeWorldTransform();
	const Matrix4& GetWorldTransform() const { return m_WorldTransform; }

	Vector2 GetForward() const { return Vector2(Math::Cos(m_Rotation), Math::Sin(m_Rotation)); }

	State GetState() const { return m_State; }
	void SetState(State state) { m_State = state; }

	class Game* GetGame() { return m_Game; }


	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	// Actor's state
	State m_State;

	// Transform
	Matrix4 m_WorldTransform;
	Vector2 m_Position;
	float m_Scale;
	float m_Rotation;
	bool m_RecomputeWorldTransform;

	std::vector<class Component*> m_Components;
	class Game* m_Game;
};

