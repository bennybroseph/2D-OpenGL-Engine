////////////////////////////////////////////////////////////
// File: LoopHandle.cpp
// Author: Ben Odom
// Date Created: 10/01/2015
////////////////////////////////////////////////////////////

#include "LoopHandle.h"

namespace LoopHandle
{
	void Init()
	{
		HWND consoleWindow = GetConsoleWindow(); // Get the current console window
		SetWindowPos(consoleWindow, 0, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOZORDER); // Move it to the Top Left and don't change its size or 'z' order

		Graphics::Init();

		Graphics::NewWindow({ 1600, 900 }, false, { 1600, 900 }, "New Window", 1);
		//Graphics::NewWindow({ 200, 900 }, false, { 200, 900 }, "New Window", 0);

		GameLoop oGameLoop;

		oGameLoop.Run();
	}

	void Handle()
	{

	}

	void Quit()
	{
		Graphics::Quit();
	}
}

