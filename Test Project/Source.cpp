#include "System.h"
#include "Graphics.h"

#include <iostream>
#include <vector>

#include <Windows.h>

int wmain()
{
	Graphics::Init();
	Graphics::NewWindow({ 1600, 900 }, false, { 1600, 900 }, "New Window", 0);
	System::Point2D<int> Temp1 = { 0, 0 };
	Graphics::NewCamera({ 150, 150 }, { 0, 0 }, Temp1, { 400, 300 }, false, { 0, 0 }, 0);
	/*System::Point2D<int> Temp2 = { 0, 0 };
	Graphics::NewCamera({ 0, 0 }, { 0, 0 }, Temp2, { 300, 300 }, false, { 0, 0 }, 0);*/

	/*Graphics::GLSurface<int> *Test4 = Graphics::LoadSurface<int>("Images/background.png");*/

	Graphics::GLSurface<int> *Test1 = Graphics::LoadSurface<int>("Images/treeSmall.png");
	Test1->Scale = { 1, 1 };
	Test1->Pos = { -100, 0 };
	Graphics::GLSurface<int> *Test2 = Graphics::LoadSurface<int>("Images/environment.png");
	Test2->Scale = { 1, 1 };
	Graphics::GLSurface<int> *Test3 = Graphics::LoadSurface<int>("Images/treeLarge.png");
	Test3->Pos = { 100, 0 };


	float X = 0, Y = 0;
	bool Run = true;
	while (Run)
	{
		if (GetAsyncKeyState(VK_LEFT))
			X += 0.03;
		if (GetAsyncKeyState(VK_RIGHT))
			X -= 0.03;
		if (GetAsyncKeyState(VK_UP))
			Y += 0.03;
		if (GetAsyncKeyState(VK_DOWN))
			Y -= 0.03;
		if (GetAsyncKeyState(VK_ESCAPE))
			Run = false;
		//Test1->Pos.X = X;
		Temp1 = { int(X), int(Y) };
		Graphics::UpdateCameras();
		Graphics::Draw();
		Graphics::Flip();
	}

	return 0;
}