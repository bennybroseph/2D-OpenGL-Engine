#include "GameLoop.h"


namespace LoopHandle
{
	void GameLoop::Update()
	{
		m_oPlayer.Handle();
	}
	void GameLoop::LateUpdate()
	{
		Collision::CheckCollisions();
		m_oPlayer.LateHandle();

		++m_iFPS;
		if (clock() > m_iTime + 1000)
		{
			printf("FPS: %d\n", m_iFPS);

			m_iTime = clock();
			m_iFPS = NULL;
		}
	}

	void GameLoop::Draw()
	{
		m_oPlayer.Draw();
		Text::Print({ 10, 10 }, false, "Something");
	}

	void GameLoop::OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
	{
		switch (ac_sdlSym)
		{
		case SDLK_ESCAPE: m_bRunning = false;

		default: m_oPlayer.OnKeyDown(ac_sdlSym, ac_uiMod, ac_sdlScancode);
		}
	}
	void GameLoop::OnKeyUp(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
	{
		switch (ac_sdlSym)
		{
		default: m_oPlayer.OnKeyUp(ac_sdlSym, ac_uiMod, ac_sdlScancode);
		}
	}

	GameLoop::GameLoop() : Loop()
	{
		Graphics::NewCamera<int>({ 0, 0 }, { 0, 0 }, m_oPlayer.GetIntPos(), { 100, 100 }, { 1, 1 }, 0, false, { 0, 0 }, 0, 0);

		Graphics::TileMap<int> TestMap("Tilemap/OriginalMap.txt", "Images/environment.png", { 128, 128 }, { 10, 7 }, { 0, 0 });

		m_iTime = clock();
		m_iFPS = NULL;
	}
	GameLoop::~GameLoop()
	{

	}
}