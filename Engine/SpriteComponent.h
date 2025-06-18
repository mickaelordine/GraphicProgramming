#pragma once
#include "Component.h"

#include "ApplicationClass.h"

class SpriteComponent : public Component
{
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(class ApplicationClass* mApp);
	/*virtual void Draw();*/
	virtual void SetTexture(class TextureClass* texture) { m_Texture = texture; };
	virtual void SetTexture(const std::string& name);

	int GetDrawOrder() const { return m_DrawOrder; }
	int GetTexHeight() const { return m_TexHeight; }
	int GetTexWidth() const { return m_TexWidth; }
protected:
	class TextureClass* m_Texture;
	int m_DrawOrder;
	int m_TexWidth;
	int m_TexHeight;
};

