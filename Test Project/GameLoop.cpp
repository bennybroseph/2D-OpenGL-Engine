#include "GameLoop.h"


namespace LoopHandle
{
	void GameLoop::Update()
	{
		m_oPlayer.Update();
	}
	void GameLoop::LateUpdate()
	{
		m_oPlayer.LateUpdate();
	}

	void GameLoop::OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
	{
		switch (ac_sdlSym)
		{
		case SDLK_ESCAPE: m_bRunning = false;
		}
	}

	GameLoop::GameLoop() : Loop()
	{
		Graphics::GLSurface<int> *Test1 = Graphics::LoadSurface<int>("Images/treeLarge.png");
		Test1->Scale = { 1, 1 };
		Test1->Pos = { 575, 360 };
		Test1->Layer = Graphics::LayerType::FOREGROUND;
		//Graphics::GLSurface<int> *Test3 = Graphics::LoadSurface<int>("Images/treeLarge.png");
		//Test3->Pos = { 100, 0 };
		//Test3->Layer = Graphics::LayerType::ALWAYS_TOP;
		//Test3->uiWorldSpace = 1;

		System::Point2D<int> Temp1 = { 0, 0 };
		Graphics::NewCamera({ 0, 0 }, { 0, 0 }, Test1->Pos, { 100, 100 }, { 1, 1 }, 0, false, { 0, 0 }, 0, 0);
		//Graphics::NewCamera({ 0, 0 }, { 0, 0 }, Temp1, { 100, 100 }, { 1, 1 }, 0, false, { 0, 0 }, 1, 0);

		Graphics::TileMap<int> TestMap("Tilemap/OriginalMap.txt", "Images/environment.png", { 128, 128 }, { 10, 7 }, { 0, 0 });
	}
	GameLoop::~GameLoop()
	{

	}
}