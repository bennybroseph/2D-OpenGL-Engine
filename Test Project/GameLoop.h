#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

#include "Loop.h"
#include "Player.h"

namespace LoopHandle
{
	class GameLoop : public Loop
	{
	private:
		Player m_oPlayer;

	public:
		void Update();
		void LateUpdate();

		void OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode);
		void OnKeyUp(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode);

		GameLoop();
		~GameLoop();
	};
}

#endif // _GAMELOOP_H_