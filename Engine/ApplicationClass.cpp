////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ApplicationClass.h"

ApplicationClass::ApplicationClass()
{
	m_Direct3D = nullptr;
	m_Camera = nullptr;
	m_ModelSquare = nullptr;
	m_ModelRect = nullptr;
	m_ColorShader = nullptr;
	m_TextureShader = nullptr;
}


ApplicationClass::ApplicationClass(const ApplicationClass& other)
{
}


ApplicationClass::~ApplicationClass()
{
}


bool ApplicationClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create and initialize the Direct3D object.
	m_Direct3D = new D3DClass;

	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -90.0f);

	// Create and initialize the square model object.
	m_ModelSquare = new SquareModel(3.0f);
	
	result = m_ModelSquare->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Square shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the square rect object.
	m_ModelRect = new RectModel(6.0f, 2.0f);

	result = m_ModelRect->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext());
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Rect shader object.", L"Error", MB_OK);
		return false;
	}

	// Create and initialize the texture shader object.
	m_TextureShader = new TextureShaderClass;

	result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void ApplicationClass::Shutdown()
{

	// Release the color shader object.
	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = nullptr;
	}

	// Release the modelSquare object.
	if (m_ModelSquare)
	{
		m_ModelSquare->Shutdown();
		delete m_ModelSquare;
		m_ModelSquare = nullptr;
	}

	// Release the modelRect object.
	if (m_ModelRect)
	{
		m_ModelRect->Shutdown();
		delete m_ModelRect;
		m_ModelRect = nullptr;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = nullptr;
	}

	// Release the Direct3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = nullptr;
	}
	
	return;
}


bool ApplicationClass::Frame()
{
	bool result;


	// Render the graphics scene.
	result = Render();
	if (!result)
	{
		return false;
	}

	return true;
}


bool ApplicationClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ModelSquare->Render(m_Direct3D->GetDeviceContext());

	// Render the model using the texture shader.
	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_ModelSquare->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_ModelSquare->GetTexture());
	if (!result)
	{
		return false;
	}

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ModelRect->Render(m_Direct3D->GetDeviceContext());

	// Render the model using the texture shader.
	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_ModelRect->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_ModelRect->GetTexture());
	if (!result)
	{
		return false;
	}

	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}