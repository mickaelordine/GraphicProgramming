#pragma once
#include "ModelClass.h"
class RectModel : public ModelClass
{
public:
	RectModel(float w, float h) : m_Width(w), m_Height(h) {}
	~RectModel() = default;
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;
	void Render(ID3D11DeviceContext*) override;
	void Shutdown() override;

protected:
	bool InitializeBuffers(ID3D11Device* device) override;

private:
	float m_Width, m_Height;

};

