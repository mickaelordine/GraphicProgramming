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
	Vector2 randPos = Vector2(0.0f, -30.0f);
	SetPosition(randPos);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Bisio"));

	// Create a square component (for collision)
	m_CircleComponent = new CircleComponent(this);
	m_CircleComponent->SetRadius(1.0f);

	// Create a move component, and set a forward speed
	m_MoveComponent = new MoveComponent(this);
	m_MoveComponent->SetForwardSpeed(30.0f);

	// Add to bricks in game
	game->AddBalls(this);
}

Ball::~Ball()
{
	GetGame()->RemoveBalls(this);
}

void Ball::UpdateActor(float deltaTime)
{
	// Do we intersect with a Brick?
	for (auto brk : GetGame()->GetBricks())
	{
		if (IntersectCircleSquare(*m_CircleComponent, *(brk->GetSquareComponent())))
		{
			// Reverse the direction of the ball
			Vector2 ballPos = GetPosition();
			Vector2 brickPos = brk->GetPosition();
			Vector2 diff = ballPos - brickPos;

			// Calcola l'angolo corrente
			float currentAngle = GetRotation();

			// Rimbalzo con ±45° a seconda della direzione
			if (fabs(diff.x) > fabs(diff.y)) // collisione da sinistra/destra
			{
				// Cambia direzione in orizzontale
				if (diff.x > 0)
					SetRotation(Math::ToRadians(135.0f)); // va in alto a sinistra
				else
					SetRotation(Math::ToRadians(45.0f));  // va in alto a destra
			}
			else // collisione dall'alto/basso
			{
				if (diff.y > 0)
					SetRotation(Math::ToRadians(315.0f)); // va in basso
				else
					SetRotation(Math::ToRadians(225.0f)); // va in alto
			}

			// The first Brick we intersect with,
			// set bricks to dead state
			brk->SetState(EDead);
			break;
		}
	}
}