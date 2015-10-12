#include "System.h"
#include "Graphics.h"

#include <iostream>
#include <vector>

#include <Windows.h>
#include <time.h>

int wmain()
{
	Graphics::Init();
	Graphics::NewWindow({ 1600, 900 }, false, { 1600, 900 }, "New Window", 0);
	Graphics::NewWindow({ 1600, 900 }, false, { 1600, 900 }, "New Window", 1);

	Graphics::GLSurface<int> *Test1 = Graphics::LoadSurface<int>("Images/treeSmall.png");
	Test1->Scale = { 1, 1 };
	Test1->Pos = { -100, 0 };
	Graphics::GLSurface<int> *Test2 = Graphics::LoadSurface<int>("Images/environment.png");
	Test2->Scale = { 1, 1 };
	Graphics::GLSurface<int> *Test3 = Graphics::LoadSurface<int>("Images/treeLarge.png");
	Test3->Pos = { 100, 0 };

	System::Point2D<int> Temp1 = { 0, 0 };
	Graphics::NewCamera({ 0, 0 }, { 0, 0 }, Test1->Pos, { 1600 / 2, 900 / 2 }, false, { 0, 0 }, 0, 0);
	System::Point2D<int> Temp2 = { 0, 0 };
	Graphics::NewCamera({ 0, 1 }, { 0, 0 }, Temp2, { 1600 / 2, 900 / 2 }, false, { 0, 0 }, 1, 0);

	/*Graphics::GLSurface<int> *Test4 = Graphics::LoadSurface<int>("Images/background.png");*/

	float X = 0, Y = 0;
	bool Run = true;

	int oldtime = clock();
	int i = 0;

	while (Run)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN:
				/* Handle key presses. */

				break;
			case SDL_QUIT:
				/* Handle quit requests (like Ctrl-c). */
				Run = false;
				break;
			}
		}

		if (GetAsyncKeyState(VK_LEFT))
			Test1->Pos.X -= 1.0;
		if (GetAsyncKeyState(VK_RIGHT))
			Test1->Pos.X += 1.0;
		if (GetAsyncKeyState(VK_UP))
			Test1->Pos.Y -= 1.0;
		if (GetAsyncKeyState(VK_DOWN))
			Test1->Pos.Y += 1.0;

		if (GetAsyncKeyState(0x41))
			Temp2.X -= 1.0;
		if (GetAsyncKeyState(0x44))
			Temp2.X += 1.0;
		if (GetAsyncKeyState(0x57))
			Temp2.Y -= 1.0;
		if (GetAsyncKeyState(0x53))
			Temp2.Y += 1.0;

		if (GetAsyncKeyState(VK_ESCAPE))
			Run = false;

		++i;
		
		if (clock() - oldtime >= 1000)
		{
			printf("FPS:%d ", i);
			oldtime = clock();
			i = 0;
		}
		Graphics::UpdateCameras();
		Graphics::Draw();
		Graphics::Flip();
	}

	return 0;
}