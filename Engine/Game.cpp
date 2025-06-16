#include "Game.h"


//Inlcudes dependecises from specific game
//#include "Ship.h"
//#include "Asteroid.h"
//#include "Random.h"

Game::Game()
	: m_SpriteShader(nullptr)
	, m_IsRunning(true)
	, m_UpdatingActors(false)
	, m_ApplicationClass(nullptr)
	, m_Hwnd(nullptr)
	, m_Input(nullptr)
{

}

Game::Game(const Game& other)
{
}

Game::~Game()
{
}

bool Game::Initialize()
{
	int screenWidth, screenHeight;
	bool result;

	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);

	// Create and initialize the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;

	m_Input->Initialize();

	m_ApplicationClass = new ApplicationClass();
	result = m_ApplicationClass->Initialize(screenWidth, screenHeight, m_Hwnd);
	if (!result)
	{
		std::cerr << "Failed to initialize ApplicationClass\n";
		return false;
	}

	// Setup altri componenti (actor system, shader logici, game logic, ecc.)
	LoadData();

	m_TicksCount = SDL_GetTicks();

	return true;
}

void Game::RunLoop()
{
	while (m_IsRunning)
	{
		ProcessInput();
		UpdateGame();
		RunSystem();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			m_IsRunning = false;
			break;
		}
	}

	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	if (keyState[SDL_SCANCODE_ESCAPE])
	{
		m_IsRunning = false;
	}

	m_UpdatingActors = true;
	for (auto actor : m_Actors)
	{
		actor->ProcessInput(keyState);
	}
	m_UpdatingActors = false;
}

void Game::UpdateGame()
{
	// Compute delta time
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), m_TicksCount + 16))
		;

	float deltaTime = (SDL_GetTicks() - m_TicksCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	m_TicksCount = SDL_GetTicks();

	// Update all actors
	m_UpdatingActors = true;
	for (auto actor : m_Actors)
	{
		actor->Update(deltaTime);
	}
	m_UpdatingActors = false;

	// Move any pending actors to mActors
	for (auto pending : m_PendingActors)
	{
		pending->ComputeWorldTransform();
		m_Actors.emplace_back(pending);
	}
	m_PendingActors.clear();

	// Add any dead actors to a temp vector
	std::vector<Actor*> deadActors;
	for (auto actor : m_Actors)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void Game::GenerateOutput()
{
	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return;
	}

	// Do the frame processing for the application class object.
	bool result = m_ApplicationClass->Frame();
	if (!result)
	{
		return;
	}

	for (auto sprite : m_Sprites)
	{
		sprite->Draw(m_ApplicationClass); //todo, add Draw function to spritecomponent
	}

	// Swap the buffers
	//SDL_GL_SwapWindow(m_Window);
}

bool Game::LoadShaders()
{
	//m_SpriteShader = new Shader();
	//if (!m_SpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	//{
	//	return false;
	//}

	//m_SpriteShader->SetActive();
	//// Set the view-projection matrix
	//Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1280.f, 720.f);
	//mSpriteShader->SetMatrixUniform("uViewProj", viewProj);
	//return true;
	return true;
}

void Game::CreateSpriteVerts()
{
	//float vertices[] = {
	//	-0.5f,  0.5f, 0.f, 0.f, 0.f, 1.0f, 0.0f, 0.0f, // rosso // top left
	//	 0.5f,  0.5f, 0.f, 1.f, 0.f, 0.0f, 1.0f, 0.0f, // verde // top right
	//	 0.5f, -0.5f, 0.f, 1.f, 1.f, 0.0f, 0.0f, 1.0f, // blu // bottom right
	//	-0.5f, -0.5f, 0.f, 0.f, 1.f, 1.0f, 1.0f, 0.0f  // giallo// bottom left
	//};

	//unsigned int indices[] = {
	//	0, 1, 2,
	//	2, 3, 0
	//};

	//mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void Game::LoadData()
{
	//// Create player's ship
	//mShip = new Ship(this);
	//mShip->SetRotation(Math::PiOver2);

	//// Create asteroids
	//const int numAsteroids = 20;
	//for (int i = 0; i < numAsteroids; i++)
	//{
	//	new Asteroid(this);
	//}
}

void Game::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!m_Actors.empty())
	{
		delete m_Actors.back();
	}

	// Destroy textures
	/*for (auto i : m_Textures)
	{
		i.second->Unload();
		delete i.second;
	}
	m_Textures.clear();*/
}

//Texture* Game::GetTexture(const std::string& fileName)
//{
//	/*Texture* tex = nullptr;
//	auto iter = m_Textures.find(fileName);
//	if (iter != m_Textures.end())
//	{
//		tex = iter->second;
//	}
//	else
//	{
//		tex = new Texture();
//		if (tex->Load(fileName))
//		{
//			m_Textures.emplace(fileName, tex);
//		}
//		else
//		{
//			delete tex;
//			tex = nullptr;
//		}
//	}
//	return tex;*/
//}

void Game::Shutdown()
{
	if (m_ApplicationClass) 
	{
		m_ApplicationClass->Shutdown();
		delete m_ApplicationClass;
		m_ApplicationClass = nullptr;
	}

	// Release the input object.
	if (m_Input)
	{
		delete m_Input;
		m_Input = 0;
	}

	UnloadData();
	/*delete m_SpriteVerts;
	m_SpriteShader->Unload();
	delete m_SpriteShader;*/
	// Shutdown the window.
	ShutdownWindows();
}

void Game::AddActor(Actor* actor)
{
	// If we're updating actors, need to add to pending
	if (m_UpdatingActors)
	{
		m_PendingActors.emplace_back(actor);
	}
	else
	{
		m_Actors.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	// Is it in pending actors?
	auto iter = std::find(m_PendingActors.begin(), m_PendingActors.end(), actor);
	if (iter != m_PendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, m_PendingActors.end() - 1);
		m_PendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(m_Actors.begin(), m_Actors.end(), actor);
	if (iter != m_Actors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, m_Actors.end() - 1);
		m_Actors.pop_back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = m_Sprites.begin();
	for (;
		iter != m_Sprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	m_Sprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(m_Sprites.begin(), m_Sprites.end(), sprite);
	m_Sprites.erase(iter);
}

/////////////////////////////////////
//SYSTEMCLASS INTEGRATION INSIDE GAME
/////////////////////////////////////

bool Game::Frame()
{
	bool result;


	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return false;
	}

	// Do the frame processing for the application class object.
	result = m_ApplicationClass->Frame();
	if (!result)
	{
		return false;
	}

	return true;
}

void Game::RunSystem() {
	MSG msg;
	bool done, result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the window or the user.
	done = false;

	// Handle the windows messages.
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// If windows signals to end the application then exit out.
	if (msg.message == WM_QUIT)
	{
		done = true;
	}
	else
	{
		// Otherwise do the frame processing.
		result = Frame();
		if (!result)
		{
			done = true;
		}
	}

	return;
}

LRESULT CALLBACK Game::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	switch (umsg)
	{
		// Check if a key has been pressed on the keyboard.
	case WM_KEYDOWN:
	{
		// If a key is pressed send it to the input object so it can record that state.
		m_Input->KeyDown((unsigned int)wparam);
		return 0;
	}

	// Check if a key has been released on the keyboard.
	case WM_KEYUP:
	{
		// If a key is released then send it to the input object so it can unset the state for that key.
		m_Input->KeyUp((unsigned int)wparam);
		return 0;
	}

	// Any other messages send to the default message handler as our application won't make use of them.
	default:
	{
		return DefWindowProc(hwnd, umsg, wparam, lparam);
	}
	}
}

void Game::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.	
	GameHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Engine";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 1280x720 resolution.
		screenWidth = 1280;
		screenHeight = 720;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth) / 2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
	}

	// Create the window with the screen settings and get the handle to it.
	m_Hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName,
		WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_Hwnd, SW_SHOW);
	SetForegroundWindow(m_Hwnd);
	SetFocus(m_Hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}

void Game::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_Hwnd);
	m_Hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// Check if the window is being destroyed.
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}

	// Check if the window is being closed.
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
	}

	// All other messages pass to the message handler in the system class.
	default:
	{
		return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
	}
	}
}
