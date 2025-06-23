#pragma once
#include "Actor.h"
class Ball : public Actor
{
public:
	Ball(class Game* game);
	~Ball();

	virtual void UpdateActor(float deltaTime) override;

private:
	class CircleComponent* m_CircleComponent;
	class MoveComponent* m_MoveComponent;
};

