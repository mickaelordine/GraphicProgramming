#pragma once
#include "Actor.h"
class Platform : public Actor
{
public:
	Platform(class Game* game);
	~Platform();

	class SquareComponent* GetSquareComponent() const { return m_SquareComponent; }

	virtual void UpdateActor(float deltaTime) override;
	void ActorInput(InputClass* keyState) override;

private:
	class SquareComponent* m_SquareComponent;
};

