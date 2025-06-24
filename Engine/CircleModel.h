#pragma once
#include "ModelClass.h"
class CircleModel : public ModelClass
{
public:
	CircleModel(float size) : m_Size(size) {};
	~CircleModel() = default;
	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext) override;
	void Render(ID3D11DeviceContext*) override;
	void Shutdown() override;

protected:
	bool InitializeBuffers(ID3D11Device* device) override;

private:
	float m_Size;
};

