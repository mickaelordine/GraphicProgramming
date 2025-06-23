////////////////////////////////////////////////////////////////////////////////
// Filename: Engine.cpp
////////////////////////////////////////////////////////////////////////////////

#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
    Game* game;
    bool result;

    game = new Game();

    // Initialize and run the game object.
    result = game->Initialize();

    if (result)
    {
        game->RunLoop(); //here the main loop is called
    }

    // Shutdown and release the game object.
    game->Shutdown();
    delete game;
    game = nullptr;

    return 0;
}
