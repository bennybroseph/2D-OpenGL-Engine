#include "LoopHandle.h"

int wmain()
{
	LoopHandle::Init();
	LoopHandle::Handle();
	LoopHandle::Quit();
	

	Graphics::GLSurface<int> *Test1 = Graphics::LoadSurface<int>("Images/treeLarge.png");
	Test1->Scale = { 1, 1 };
	Test1->Pos = { 575, 360 };
	Test1->Layer = Graphics::LayerType::ALWAYS_TOP;
	//Graphics::GLSurface<int> *Test3 = Graphics::LoadSurface<int>("Images/treeLarge.png");
	//Test3->Pos = { 100, 0 };
	//Test3->Layer = Graphics::LayerType::ALWAYS_TOP;
	//Test3->uiWorldSpace = 1;

	System::Point2D<int> Temp1 = { 0, 0 };
	Graphics::NewCamera({ 0, 0 }, { 0, 0 }, Test1->Pos, { 100, 100 }, { 1, 1 }, 0, false, { 0, 0 }, 0, 0);
	//Graphics::NewCamera({ 0, 0 }, { 0, 0 }, Temp1, { 100, 100 }, { 1, 1 }, 0, false, { 0, 0 }, 1, 0);

	Graphics::TileMap<int> TestMap("Tilemap/OriginalMap.txt", "Images/environment.png", { 128, 128 }, { 10, 7 }, { 0, 0 });

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
			Test1->Pos.X -= 5.0;
		if (GetAsyncKeyState(VK_RIGHT))
			Test1->Pos.X += 5.0;
		if (GetAsyncKeyState(VK_UP))
			Test1->Pos.Y -= 5.0;
		if (GetAsyncKeyState(VK_DOWN))
			Test1->Pos.Y += 5.0;

		/*if (GetAsyncKeyState(0x41))
			Temp2.X -= 1.0;
		if (GetAsyncKeyState(0x44))
			Temp2.X += 1.0;
		if (GetAsyncKeyState(0x57))
			Temp2.Y -= 1.0;
		if (GetAsyncKeyState(0x53))
			Temp2.Y += 1.0;*/

		if (GetAsyncKeyState(VK_ESCAPE))
			Run = false;

		++i;

		if (clock() - oldtime >= 1000)
		{
			printf("FPS:%d ", i);
			oldtime = clock();
			i = 0;
		}
		Graphics::Draw();
		Graphics::Flip();
	}

	return 0;
}