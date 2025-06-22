#include "Brick.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "SquareComponent.h"
#include "Random.h"

Brick::Brick(Game* game)
	: Actor(game)
	, m_SquareComponent(nullptr)
{
	// Initialize to random position/orientation
	SetRotation(Random::GetFloatRange(0.0f, 0.0f));

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Brick"));


	// Create a square component (for collision)
	m_SquareComponent = new SquareComponent(this);
	m_SquareComponent->SetHeight(2.0f);
	m_SquareComponent->SetWidth(4.0f);

	// Add to bricks in game
	game->AddBricks(this);
}

Brick::~Brick()
{
	GetGame()->RemoveBricks(this);
}