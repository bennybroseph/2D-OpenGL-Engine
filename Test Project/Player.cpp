#include "Player.h"

const unsigned int SPEED = 5;

void Player::Update()
{
	if (m_bUp || m_bDown || m_bLeft || m_bRight)
	{
		m_bMove = true;
		m_fVelocity = { 0, 0 };

		if (m_bUp)
			m_fVelocity.Y += -1;
		if (m_bDown)
			m_fVelocity.Y += 1;

		if (m_bLeft)
			m_fVelocity.X += -1;
		if (m_bRight)
			m_fVelocity.X += 1;

		System::ToAngular(m_fVelocity, SPEED);
	}
	else
		m_bMove = false;
}

void Player::LateUpdate()
{
	m_glSurface->Pos = m_iPos;
	other.UpdateBB();
}

void Player::OnCollision(Object& a_oOther)
{
	//printf("Collision ");

	if (m_fVelocity.Y < 0 && m_fVelocity.X == 0.0f)
		m_fPos.Y = a_oOther.GetBoundingBox().fMax.Y + m_glSurface->OffsetD.H / 2 + 1.0f;
	if (m_fVelocity.Y > 0 && m_fVelocity.X == 0.0f)
		m_fPos.Y = a_oOther.GetBoundingBox().fMin.Y - m_glSurface->OffsetD.H / 2 - 1.0f;

	if (m_fVelocity.X < 0 && m_fVelocity.Y == 0.0f)
		m_fPos.X = a_oOther.GetBoundingBox().fMax.X + m_glSurface->OffsetD.W / 2 + 1.0f;
	if (m_fVelocity.X > 0 && m_fVelocity.Y == 0.0f)
		m_fPos.X = a_oOther.GetBoundingBox().fMin.X - m_glSurface->OffsetD.W / 2 - 1.0f;
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

Player::Player() : Object()
{
	m_glSurface = Graphics::LoadSurface<int>("Images/treeLarge.png");
	m_glSurface->Layer = Graphics::LayerType::FOREGROUND;

	m_bbBoundingBox = Collision::NewBoundingBox(this, { (float)m_glSurface->OffsetD.W, (float)m_glSurface->OffsetD.H }, m_fPos, false, true);

	m_fPos = { 200, 200 };

	auto temp = Graphics::LoadSurface<int>("Images/treeLarge.png");
	temp->Pos = { 0,0 };
	temp->Layer = Graphics::LayerType::FOREGROUND;

	other.m_bbBoundingBox = Collision::NewBoundingBox(&other, { (float)m_glSurface->OffsetD.W, (float)m_glSurface->OffsetD.H }, { 0, 0 }, false, true);
}
Player::~Player()
{

}

