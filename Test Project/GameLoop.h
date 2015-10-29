#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

#include "Player.h"

#include <Loop.h>
#include <Text.h>
#include <TileMap.h>

#include <time.h>

namespace LoopHandle
{
	class GameLoop : public Loop
	{
	private:
		Player m_oPlayer;

		int m_iFPS, m_iTime;

	public:
		void Update();
		void LateUpdate();

		void Draw();

		void OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode);
		void OnKeyUp(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode);

		GameLoop();
		~GameLoop();
	};
}

#endif // _GAMELOOP_H_