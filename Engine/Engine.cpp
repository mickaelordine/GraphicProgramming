////////////////////////////////////////////////////////////////////////////////
// Filename: Engine.cpp
////////////////////////////////////////////////////////////////////////////////
#include "SystemClass.h"
#include "Game.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
    SystemClass* System;
    Game* game;
    bool result;


    // Create the system object.
    System = new SystemClass;

    // Initialize and run the system object.
    result = System->Initialize();

    if (result)
    {
		System->Run(); //here the main loop is called
    }

    // Shutdown and release the system object.
    System->Shutdown();
    delete System;
    System = 0;

    return 0;
}
