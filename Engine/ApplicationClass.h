////////////////////////////////////////////////////////////////////////////////
// Filename: applicationclass.h
////////////////////////////////////////////////////////////////////////////////
#pragma once


//////////////
// INCLUDES //
//////////////
#include <windows.h>
#include "SDL3/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "D3DClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "SquareModel.h"
#include "RectModel.h"
#include "ColorShaderClass.h"
#include "TextureShaderClass.h"
#include "EnumDictionary.h"

///////////////////////
//		STRUCTS		 //
///////////////////////
struct RGBA
{
	float r, g, b, a;
};


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.3f;

////////////////////////////////////////////////////////////////////////////////
// Class name: ApplicationClass
////////////////////////////////////////////////////////////////////////////////
class ApplicationClass
{
public:
	ApplicationClass();
	ApplicationClass(const ApplicationClass&);
	~ApplicationClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame();
	D3DClass* GetD3D() { return m_Direct3D; }
	CameraClass* GetCamera() { return m_Camera; }
	ModelClass* GetModelSquare() { return m_ModelSquare; }
	ModelClass* GetModelRect() { return m_ModelRect; }
	TextureShaderClass* GetTextureShader() { return m_TextureShader; }

private:
	bool Render();

private:
	D3DClass* m_Direct3D;
	CameraClass* m_Camera;
	ModelClass* m_ModelSquare;
	ModelClass* m_ModelRect;
	ColorShaderClass* m_ColorShader;
	TextureShaderClass* m_TextureShader;
};
