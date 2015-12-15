#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <Collision.h>
#include <GLSprite.h>

class Player : public Collision::Object
{
private:
	bool m_bUp, m_bDown, m_bLeft, m_bRight;

	Graphics::GLSurface<int>* m_glSurface;

	GLSprite<float>* m_glPlayerSprite;

	Object other;

public:
	void Update();
	void LateUpdate();

	void Draw();

	//void OnBoxCollision(Object& a_oOther);
	//void OnCircleCollision(Object& a_oOther);

	void OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode);
	void OnKeyUp(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode);

	Player();
	~Player();
};

#endif // _PLAYER_H_

