#include "CircleModel.h"

bool CircleModel::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext)
{
	bool result = InitializeBuffers(device);
	if (!result)
	{
		return false; // Failed to initialize buffers
	}

	LoadTexture(device, deviceContext, "../Engine/Textures/Claudio_Bisio.tga"); // Load a default texture

	return true;
}

void CircleModel::Render(ID3D11DeviceContext* deviceContext)
{
	RenderBuffers(deviceContext); // Render the buffers
}

void CircleModel::Shutdown()
{
	ShutdownBuffers();
}


bool CircleModel::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	int numSegments = 12;
	m_vertexCount = 14; // 1 centro + numSegments + 1 per chiusura

	// Set the number of indices in the index array.
	m_indexCount = 14;
	m_indexCount = numSegments * 3;

	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if (!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}

	///////////////////////////////////
	// LOADING INFORMATION TO RENDER A sphere (14 VERTICES)
	///////////////////////////////////

	vertices[0].position = XMFLOAT3(0.0f, 0.0f, 0.0f); // centro
	vertices[0].texture = XMFLOAT2(0.5f, 0.5f); // centro texture

	for (int i = 0; i <= numSegments; ++i) {
		float angle = i * 2.0f * 3.14159265f / numSegments;
		float x = cosf(angle);
		float y = sinf(angle);

		int vi = i + 1; // vertice corrente (offset di +1 per lasciare posto al centro)
		vertices[vi].position = XMFLOAT3(x * m_Size, y * m_Size, 0.0f);
		float u = (x * 0.5f) + 0.5f;
		float v = (-y * 0.5f) + 0.5f;
		vertices[vi].texture = XMFLOAT2(u, v);
	}

	// centro è 0
	for (int i = 0; i < numSegments; ++i) {
		indices[i * 3 + 0] = 0;            // centro
		indices[i * 3 + 1] = i + 1;        // vertice corrente
		indices[i * 3 + 2] = i + 2;        // vertice successivo (chiude il triangolo)
	}
	

	///////////////////////////////////
	// LOADING INFORMATION TO RENDER A Sphere (14 VERTICES)
	///////////////////////////////////

	// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}