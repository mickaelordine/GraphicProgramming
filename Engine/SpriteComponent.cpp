#include "SpriteComponent.h"
#include "Actor.h"


SpriteComponent::SpriteComponent(Actor* owner, int order) 
	: Component(owner)
	, m_DrawOrder(order)
{
}

SpriteComponent::~SpriteComponent() {

}

void SpriteComponent::Draw(class ApplicationClass* application) {
	if (application == nullptr)
		return;

	application->Frame();

	//for now we call Frame(), but we will need to tell the Application What to render.
}
