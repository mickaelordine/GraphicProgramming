#include "Ball.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "SquareComponent.h"
#include "Random.h"
#include "CircleComponent.h"
#include "MoveComponent.h"
#include "Brick.h"


Ball::Ball(Game* game)
	:Actor(game)
	, m_CircleComponent(nullptr)
	, m_MoveComponent(nullptr)
{
	// Initialize to random position/orientation
	Vector2 randPos = Vector2(0.0f, 0.0f);
	SetPosition(randPos);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Bisio"));

	// Create a square component (for collision)
	m_CircleComponent = new CircleComponent(this);
	m_CircleComponent->SetRadius(25.0f);

	// Create a move component, and set a forward speed
	m_MoveComponent = new MoveComponent(this);
	m_MoveComponent->SetForwardSpeed(100.0f);

	// Add to bricks in game
	game->AddBalls(this);
}

Ball::~Ball()
{
	//GetGame()->RemoveBall(this);
}

void Ball::UpdateActor(float deltaTime)
{
	// Do we intersect with a Brick?
	for (auto brk : GetGame()->GetBricks())
	{
		if (IntersectCircleSquare(*m_CircleComponent, *(brk->GetSquareComponent())))
		{
			// The first Brick we intersect with,
			// set bricks to dead state
			brk->SetState(EDead);
			break;
		}
	}
}