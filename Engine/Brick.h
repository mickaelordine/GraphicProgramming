#pragma once
#include "Actor.h"
class Brick : public Actor
{

public:
	Brick(class Game* game);
	~Brick();

	class SquareComponent* GetSquareComponent() const { return m_SquareComponent; }


private:
	class SquareComponent* m_SquareComponent;

};

