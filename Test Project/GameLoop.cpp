#include "GameLoop.h"

const System::Point2D<int> Center = { 0, 0 };

namespace LoopHandle
{
	void GameLoop::Update()
	{
		m_oPlayer.Handle();
	}
	void GameLoop::LateUpdate()
	{
		m_oPlayer.LateHandle();

		++m_iFPS;
		if (clock() > m_iTime + 1000)
		{
			printf("FPS: %d\n", m_iFPS);

			m_iTime = clock();
			m_iFPS = NULL;
		}

		char szBuffer[256];

		sprintf_s(szBuffer, "(%d, %d)", m_oPlayer.GetIntPos().X, m_oPlayer.GetIntPos().Y);
		Text::ReloadTextBlock(m_ttfTextBlock, false, szBuffer);

		m_ttfTextBlock->glSurface->Pos = m_oPlayer.GetIntPos();
	}

	void GameLoop::Draw()
	{
		m_oPlayer.Draw();
	}

	void GameLoop::OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
	{
		switch (ac_sdlSym)
		{
		case SDLK_ESCAPE: m_bRunning = false;

		default: m_oPlayer.OnKeyDown(ac_sdlSym, ac_uiMod, ac_sdlScancode); break;
		}
	}
	void GameLoop::OnKeyUp(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
	{
		switch (ac_sdlSym)
		{
		default: m_oPlayer.OnKeyUp(ac_sdlSym, ac_uiMod, ac_sdlScancode); break;
		}
	}

	GameLoop::GameLoop() : Loop()
	{
		//Graphics::NewCamera({ 0, 0 }, { 0, 0 }, m_oPlayer.GetIntPos(), { 100, 100 }, { 1, 1 }, 0, false, { 0, 0 }, 0, 0);
		Graphics::NewCamera({ 0, 0 }, { 0, 0 }, Center, { 100, 100 }, { 1, 1 }, 0, false, { 0, 0 }, 0, 0);

		Graphics::TileMap<int> TestMap("Tilemap/OriginalMap.txt", "Images/environment.png", { 128, 128 }, { 10, 7 }, { (-128*9)/2, (-128*6)/2 });

		m_ttfTextBlock = Text::LoadTextBlock({ 0, 0 }, false, "0, 0");

		m_iTime = clock();
		m_iFPS = NULL;

		Graphics::Sort();
	}
	GameLoop::~GameLoop()
	{

	}
}