#include "System.h"
#include "Graphics.h"

#include <iostream>
#include <vector>

int wmain()
{
	const int* p;
	int g = 2;
	int f = 3;
	p = &g;
	p = &f;

	Graphics::Init();
	Graphics::NewWindow({ 600, 600 }, false, { 600, 600 }, "New Window", 0);
	System::Point2D<float> Temp = { 0,0 };
	Graphics::NewCamera(Temp, { 0, 0 }, { 0, 0 }, { 600, 600 }, false, { 0, 0 }, 0);

	Graphics::GLSurface<float> *Test = Graphics::LoadSurface<float>("Images/sheet_tanks.png");

	while (true)
	{
		Graphics::Draw();
		Graphics::Flip();
	}

	system("pause");
	return 0;
}