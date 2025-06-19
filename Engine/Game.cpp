#include "Game.h"
#include "Random.h"

//////////////////////////////////////////
//Inlcudes dependecises from specific game
//////////////////////////////////////////
#include "Brick.h"
#include "Ball.h"

Game::Game()
	: m_IsRunning(true)
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
		case SDL_EVENT_QUIT:
			m_IsRunning = false;
			break;
		}
	}

	const bool* keyState = SDL_GetKeyboardState(NULL);
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
	while (!(SDL_GetTicks() >= m_TicksCount + 16))
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

	//std::cout << "Game::UpdateGame() - Bisio Position: X:" << m_Balls.at(0)->GetPosition().x << " Y: " << m_Balls.at(0)->GetPosition().y << std::endl;
}

void Game::GenerateOutput()
{
	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsKeyDown(VK_ESCAPE))
	{
		return;
	}

	m_ApplicationClass->GetD3D()->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);// Clear the screen to black
	m_ApplicationClass->GetCamera()->Render();

	for (auto sprite : m_Sprites) {
		sprite->Draw(m_ApplicationClass);
	}
	//error Exception thrown: read access violation. sprite->was 0xFFFFFFFFFFFFFFDF.

	m_ApplicationClass->GetD3D()->EndScene();
}

bool Game::LoadTexture(const std::string& name, const char* filepath)
{
	if (m_TextureMap.count(name)) return true;
	TextureClass* tex = new TextureClass();
	if (!tex->Initialize(m_ApplicationClass->GetD3D()->GetDevice(), m_ApplicationClass->GetD3D()->GetDeviceContext(), filepath))
	{
		delete tex; 
		return false;
	}
	if (m_TextureMap.count(name)) 
		return true;
	m_TextureMap[name] = tex;
	return true;
}

TextureClass* Game::GetTexture(const std::string& name) {
	auto it = m_TextureMap.find(name);
	return it != m_TextureMap.end() ? it->second : nullptr;
}

void Game::LoadData()
{
	//load all the necessary texture for the game
	LoadTexture("Bisio", "../Engine/Textures/Claudio_Bisio.tga");
	LoadTexture("Brick", "../Engine/Textures/Brick.tga");
	LoadTexture("Ball", "../Engine/Textures/sample-tga-files-sample_640x426.tga");

	//// Create player's ship
	//mShip = new Ship(this);
	//mShip->SetRotation(Math::PiOver2);

	//create ball
	new Ball(this);

	// Create Bricks
	const int numBricks = 20;
	for (int i = 0; i < numBricks; i++)
	{
		new Brick(this);
	}

	
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

void Game::AddBricks(class Brick* brk) {
	m_Bricks.emplace_back(brk);
}
void Game::AddBalls(class Ball* ball) {
	m_Balls.emplace_back(ball);
}
void Game::RemoveBricks(class Brick* brk) {
	auto iter = std::find(m_Bricks.begin(),
		m_Bricks.end(), brk);
	if (iter != m_Bricks.end())
	{
		m_Bricks.erase(iter);
	}
}
void Game::RemoveBalls(class Ball* ball) {
	auto iter = std::find(m_Balls.begin(),
		m_Balls.end(), ball);
	if (iter != m_Balls.end())
	{
		m_Balls.erase(iter);
	}
}

/////////////////////////////////////
//SYSTEMCLASS INTEGRATION INSIDE GAME
/////////////////////////////////////

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
		GenerateOutput();
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
