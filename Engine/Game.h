#pragma once
///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define WIN32_LEAN_AND_MEAN

//////////////
// INCLUDES //
//////////////
#include <windows.h>

#include "SDL3/SDL.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "ApplicationClass.h"
#include "inputclass.h"
#include <algorithm>
#include <iostream>

#include "Actor.h"
#include "SpriteComponent.h"
#include "SystemClass.h"

class Game
{
public:
	Game();
	Game(const Game&);
	~Game();
	bool Initialize();
	void RunLoop(); //Run() in SystemClass
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	//class Texture* GetTexture(const std::string& fileName);

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	// Game-specific (add/remove asteroid)
	/*void AddAsteroid(class Asteroid* ast);
	void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }*/
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool LoadShaders();
	void CreateSpriteVerts();
	void LoadData();
	void UnloadData();

	//SystemClass integration
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
	void RunSystem();

	// Map of textures loaded
	std::unordered_map<std::string, class Texture*> m_Textures;
	// All the actors in the game
	std::vector<class Actor*> m_Actors;
	// Any pending actors
	std::vector<class Actor*> m_PendingActors;
	// All the sprite components drawn
	std::vector<class SpriteComponent*> m_Sprites;

	// Sprite shader
	class Shader* m_SpriteShader;
	// Sprite vertex array
	class VertexArray* m_SpriteVerts;

	//SystemClassIntegration procedure
	class ApplicationClass* m_ApplicationClass;
	HWND m_Hwnd;
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	InputClass* m_Input;


	/*SDL_Window* m_Window;
	SDL_GLContext m_Context;*/
	Uint64 m_TicksCount;
	bool m_IsRunning;
	// Track if we're updating actors right now
	bool m_UpdatingActors;

	

	// Game-specific
	/*class Ship* m_Ship;
	std::vector<class Asteroid*> m_Asteroids;*/
};


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/////////////
// GLOBALS //
/////////////
static Game* GameHandle = 0;

