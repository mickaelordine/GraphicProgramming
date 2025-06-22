#pragma once
#include "Actor.h"
class BouncingWall : public Actor
{
public:

	BouncingWall(class Game* game, Vector2 position, float rotation);
	~BouncingWall();

	class SquareComponent* GetSquareComponent() const { return m_SquareComponent; }


private:
	class SquareComponent* m_SquareComponent;
};

