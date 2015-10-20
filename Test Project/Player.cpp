#include "Player.h"

const unsigned int SPEED = 5;

void Player::Update()
{
	if (m_bUp || m_bDown || m_bLeft || m_bRight)
	{
		m_bMove = true;

		if (m_bUp)
			m_Velocity = { SPEED, System::AngularDir::UP };
		if (m_bDown)
			m_Velocity = { SPEED, System::AngularDir::DOWN };

		if (m_bLeft)
			m_Velocity = { SPEED, System::AngularDir::LEFT };
		if (m_bRight)
			m_Velocity = { SPEED, System::AngularDir::RIGHT };

		/*if (m_bUp && m_bLeft)
			m_Velocity = { SPEED, System::AngularDir::UP_LEFT };
		if (m_bUp && m_bRight)
			m_Velocity = { SPEED, System::AngularDir::UP_RIGHT };

		if (m_bDown && m_bLeft)
			m_Velocity = { SPEED, System::AngularDir::DOWN_LEFT };
		if (m_bDown && m_bRight)
			m_Velocity = { SPEED, System::AngularDir::DOWN_RIGHT };*/
	}
	else
		m_bMove = false;
}

void Player::OnKeyDown(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
{
	switch (ac_sdlSym)
	{
	case SDLK_UP: m_bUp = true; break;
	case SDLK_DOWN: m_bDown = true; break;
	case SDLK_LEFT: m_bLeft = true; break;
	case SDLK_RIGHT:m_bRight = true; break;
	default: break;
	}
}

void Player::OnKeyUp(const SDL_Keycode ac_sdlSym, const Uint16 ac_uiMod, const SDL_Scancode ac_sdlScancode)
{
	switch (ac_sdlSym)
	{
	case SDLK_UP: m_bUp = false; break;
	case SDLK_DOWN: m_bDown = false; break;
	case SDLK_LEFT: m_bLeft = false; break;
	case SDLK_RIGHT:m_bRight = false; break;

	default: break;
	}
}

Player::Player() : Object<int>()
{
	m_glSurface = Graphics::LoadSurface<int>("Images/treeLarge.png");
	m_glSurface->Layer = Graphics::LayerType::FOREGROUND;

	m_bbBoundingBox = Collision::NewBoundingBox(this, m_glSurface->OffsetD, false, true);
}
Player::~Player()
{

}
