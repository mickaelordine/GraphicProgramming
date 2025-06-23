#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "TextureClass.h"
#include "EnumDictionary.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
protected:

	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
	};

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();
	virtual bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext) = 0;
	virtual void Shutdown();
	virtual void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();

protected:
	void ShutdownBuffers();
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, const char*);
	void RenderBuffers(ID3D11DeviceContext*);

private:
	//Initialize different buffers
	virtual bool InitializeBuffers(ID3D11Device*) = 0;
	/*bool InitializeBuffersSquare(ID3D11Device*);
	bool InitializeBuffersRect(ID3D11Device*, float width, float height);*/
	void ReleaseTexture();
	void SetTexture(TextureClass* tex);
	ID3D11ShaderResourceView* GetTextureView() const;

private:
	TextureClass* m_Texture;

protected:
	int m_vertexCount, m_indexCount;
	ID3D11Buffer* m_vertexBuffer, * m_indexBuffer;
};

