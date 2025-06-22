#include "Platform.h"

#include "Ball.h"
#include "SpriteComponent.h"
#include "Game.h"
#include "SquareComponent.h"
#include "Random.h"
#include "CircleComponent.h"
#include "MoveComponent.h"
#include "Brick.h"
#include "BouncingWall.h"
#include "InputComponent.h"


Platform::Platform(Game* game)
	:Actor(game)
	, m_SquareComponent(nullptr)
{
	// Initialize to random position/orientation
	Vector2 intialPos = Vector2(0.0f, -35.0f);
	SetPosition(intialPos);

	SetRotation(0.0f);

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Platform"));

	// Create a square component (for collision)
	m_SquareComponent = new SquareComponent(this);
	m_SquareComponent->SetHeight(5.0f);
	m_SquareComponent->SetWidth(15.0f);

	// Create an input component and set keys/speed
	InputComponent* ic = new InputComponent(this);
	ic->SetRightKey(SDL_SCANCODE_A);
	ic->SetLeftKey(SDL_SCANCODE_D);
	ic->SetMaxHorzSpeed(65.0f);
}

Platform::~Platform()
{
}

void Platform::UpdateActor(float deltaTime)
{
	
}

void Platform::ActorInput(InputClass* keyState)
{
	
}
