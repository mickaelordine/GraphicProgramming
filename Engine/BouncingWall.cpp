#include "BouncingWall.h"
#include "Game.h"
#include "SquareComponent.h"
#include "Random.h"

BouncingWall::BouncingWall(class Game* game, Vector2 position, float rotation) 
	: Actor(game)
	, m_SquareComponent(nullptr)
{
	// Initialize WallPosition and rotation
	SetPosition(position);
	SetRotation(rotation);

	// Create a square component (for collision)
	m_SquareComponent = new SquareComponent(this);
	m_SquareComponent->SetHeight(25.0f);
	m_SquareComponent->SetWidth(10000.0f);

	SpriteComponent* sc = new SpriteComponent(this, EnumDictionary::BufferType::Rectangle);
	sc->SetTexture(game->GetTexture("Ball"));

	// Add to bricks in game
	game->AddWalls(this);
}
BouncingWall::~BouncingWall() {
	GetGame()->RemoveWalls(this);
}
