#include "CircleComponent.h"
#include "SquareComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(class Actor* owner)
	:Component(owner)
	, m_Radius(0.0f)
{

}

const Vector2& CircleComponent::GetCenter() const
{
	return m_Owner->GetPosition();
}

float CircleComponent::GetRadius() const
{
	return m_Owner->GetScale() * m_Radius;
}

bool IntersectCircleCircle(const CircleComponent& a, const CircleComponent& b)
{
	// Calculate distance squared
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();

	// Calculate sum of radii squared
	float radiiSq = a.GetRadius() + b.GetRadius();
	radiiSq *= radiiSq;

	return distSq <= radiiSq;
}

//TODO: potrebbe servire la restituzione di una struttura per ottenere la normale così da sapere dove farlo andare dopo la collisione
bool IntersectCircleSquare(const CircleComponent& a, const SquareComponent& b)
{
	Vector2 circleCenter = a.GetCenter();
	Vector2 squareCenter = b.GetCenter();

	float halfW = b.GetWidth() * 0.5f;
	float halfH = b.GetHeight() * 0.5f;

	float dx = std::max(std::abs(circleCenter.x - squareCenter.x) - halfW, 0.0f);
	float dy = std::max(std::abs(circleCenter.y - squareCenter.y) - halfH, 0.0f);

	return (dx * dx + dy * dy) <= (a.GetRadius() * a.GetRadius());
}

