#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:m_State(EActive)
	, m_Position(Vector2::Zero)
	, m_Scale(1.0f)
	, m_Rotation(0.0f)
	, m_Game(game)
	, m_RecomputeWorldTransform(true)
{
	m_Game->AddActor(this);
}

Actor::~Actor()
{
	m_Game->RemoveActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!m_Components.empty())
	{
		delete m_Components.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (m_State == EActive)
	{
		ComputeWorldTransform();

		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);

		ComputeWorldTransform();
	}
}

void Actor::UpdateComponents(float deltaTime)
{
	for (auto comp : m_Components)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(InputClass* keyState)
{
	if (m_State == EActive)
	{
		// First process input for components
		for (auto comp : m_Components)
		{
			comp->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

void Actor::ActorInput(InputClass* keyState)
{
}

void Actor::ComputeWorldTransform()
{
	if (m_RecomputeWorldTransform)
	{
		m_RecomputeWorldTransform = false;
		// Scale, then rotate, then translate
		m_WorldTransform = Matrix4::CreateScale(m_Scale);
		m_WorldTransform *= Matrix4::CreateRotationZ(m_Rotation);
		m_WorldTransform *= Matrix4::CreateTranslation(Vector3(m_Position.x, m_Position.y, 0.0f));

		// Inform components world transform updated
		for (auto comp : m_Components)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}

void Actor::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = m_Components.begin();
	for (;
		iter != m_Components.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	m_Components.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = std::find(m_Components.begin(), m_Components.end(), component);
	if (iter != m_Components.end())
	{
		m_Components.erase(iter);
	}
}
