#pragma once
#include "Component.h"
#include "Math.h"

class SquareComponent;

class CircleComponent : public Component
{
public:
	CircleComponent(class Actor* owner);

	void SetRadius(float radius) { m_Radius = radius; }
	float GetRadius() const;

	const Vector2& GetCenter() const;
private:
	float m_Radius;
};

bool IntersectCircleCircle(const CircleComponent& a, const CircleComponent& b);
bool IntersectCircleSquare(const CircleComponent& a, const SquareComponent& b);

