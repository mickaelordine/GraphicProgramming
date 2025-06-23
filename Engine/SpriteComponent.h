#pragma once
#include "Component.h"

#include "ApplicationClass.h"
#include "EnumDictionary.h"

class SpriteComponent : public Component
{
public:
	// (Lower draw order corresponds with further back)
	SpriteComponent(class Actor* owner, EnumDictionary::BufferType type, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(class ApplicationClass* mApp);
	/*virtual void Draw();*/
	virtual void SetTexture(class TextureClass* texture) { m_Texture = texture; };
	virtual void SetTexture(const std::string& name);

	int GetDrawOrder() const { return m_DrawOrder; }

protected:
	class TextureClass* m_Texture;
	int m_DrawOrder;
	EnumDictionary::BufferType m_Type;
};

