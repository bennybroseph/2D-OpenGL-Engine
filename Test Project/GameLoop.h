#ifndef _GAMELOOP_H_
#define _GAMELOOP_H_

#include "Player.h"
#include "Enemy.h"

#include <Loop.h>
#include <Time.h>
#include <Text.h>
#include <TileMap.h>

#include <time.h>

namespace LoopHandle
{
	class GameLoop : public Loop
	{
	private:
		Player m_oPlayer;
		std::vector<Enemy*> m_oEnemy;
		Text::TextBlock<int>* m_ttfTextBlock, *m_ttfShadow;
		Text::TextBlock<int>* m_ttfFPS, *m_ttfShadowFPS;

		int m_iFPS, m_iTime;

	public:
		void Update();
		void LateUpdate();

		void Draw();

		void OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode);
		void OnKeyUp(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode);

		void OnExit();

		GameLoop();
		~GameLoop();
	};
}

#endif // _GAMELOOP_H_