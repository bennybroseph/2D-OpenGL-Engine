#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Object.h"

class Player : public Collision::Object<int>
{
private:
	bool m_bUp, m_bDown, m_bLeft, m_bRight;

public:
	void Update();

	void OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode);
	void OnKeyUp(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode);

	Player();
	~Player();
};

#endif // _PLAYER_H_

