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

	TextureClass* GetTexture(const std::string& name);
	std::vector<class Brick*> GetBricks() { return m_Bricks; };
	std::vector<class Ball*> GetBalls() { return m_Balls; };
	std::vector<class BouncingWall*> GetWalls() { return m_Walls; };
	class Platform* GetPlatform() { return m_Platform; };

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

	// Game-specific (add/remove Balls/Bricks)
	void AddBricks(class Brick* brk);
	void AddBalls(class Ball* ball);
	void RemoveBricks(class Brick* brk);
	void RemoveBalls(class Ball* ball);
	void AddWalls(class BouncingWall* wall);
	void RemoveWalls(class BouncingWall* wall);
	/*void RemoveAsteroid(class Asteroid* ast);
	std::vector<class Asteroid*>& GetAsteroids() { return mAsteroids; }*/
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	bool LoadTexture(const std::string& name,const char* filepath);
	void LoadData();
	void UnloadData();

	//SystemClass integration
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
	void RunSystem();

	// Map of textures loaded
	std::unordered_map<std::string, class TextureClass*> m_TextureMap;
	// All the actors in the game
	std::vector<class Actor*> m_Actors;
	// Any pending actors
	std::vector<class Actor*> m_PendingActors;
	// All the sprite components drawn
	std::vector<class SpriteComponent*> m_Sprites;

	//// Sprite shader
	//class Shader* m_SpriteShader;
	//// Sprite vertex array
	//class VertexArray* m_SpriteVerts;

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
	//class Ship* m_Ship;
	std::vector<class Brick*> m_Bricks;
	std::vector<class Ball*> m_Balls;
	std::vector<class BouncingWall*> m_Walls;
	class Platform* m_Platform;
};


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/////////////
// GLOBALS //
/////////////
static Game* GameHandle = 0;

