#pragma once
#include <cstdint>
#include "InputClass.h"

class Component
{
public:
	// Constructor
	// (the lower the update order, the earlier the component updates)
	Component(class Actor* owner, int updateOrder = 100);
	// Destructor
	virtual ~Component();
	// Update this component by delta time
	virtual void Update(float deltaTime);
	// Process input for this component
	virtual void ProcessInput(InputClass* keyState) {}
	// Called when world transform changes
	virtual void OnUpdateWorldTransform() {}

	int GetUpdateOrder() const { return m_UpdateOrder; }
protected:
	// Owning actor
	class Actor* m_Owner;
	// Update order of component
	int m_UpdateOrder;
};

