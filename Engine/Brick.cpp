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
	Vector2 randPos = Random::GetVector(Vector2(-512.0f, -384.0f),
		Vector2(512.0f, 384.0f));
	SetPosition(randPos);

	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("../Engine/Textures/Claudio_Bisio.tga"));


	// Create a square component (for collision)
	m_SquareComponent = new SquareComponent(this);
	m_SquareComponent->SetHeight(25.0f);
	m_SquareComponent->SetWidth(25.0f);

	// Add to bricks in game
	game->AddBricks(this);
}

Brick::~Brick()
{
	//GetGame()->RemoveBricks(this);
}