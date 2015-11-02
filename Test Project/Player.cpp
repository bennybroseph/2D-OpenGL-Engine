#include "Player.h"

const float SPEED = 5;

void Player::Update()
{
	if (m_bUp || m_bDown || m_bLeft || m_bRight)
	{
		//m_fVelocity = { 0, 0 };
		m_fVelocity.X = 0;

		if (m_bUp)
			m_fVelocity.Y += -1;
		if (m_bDown)
			m_fVelocity.Y += 1;

		if (m_bLeft)
			m_fVelocity.X += -SPEED;
		if (m_bRight)
			m_fVelocity.X += SPEED;

		//System::ToAngular(m_fVelocity, SPEED);
	}
	else
	{
		m_fVelocity.X = 0;
	}
}

void Player::LateUpdate()
{
	m_glSurface->Pos = m_iPos;
	other.UpdateBB();
}

void Player::Draw()
{
	System::Point2D<float> Center = { 800, 450 };

	//Graphics::DrawLine(m_fPos + Center, (m_fPos + Center) + (50.0f * m_fVelocity), { 255, 255, 255, 255 });
}

//void Player::OnBoxCollision(Object& a_oOther)
//{
//
//}

//void Player::OnCircleCollision(Object& a_oOther)
//{
//	printf("Collision! ");
//	/*auto i = atan2f(m_fPrevPos.Y - a_oOther.GetBC().fCenter.Y, m_fPrevPos.X - a_oOther.GetBC().fCenter.X);
//	m_fPos = {
//		a_oOther.GetBC().fCenter.X + ((m_bbBoundingBox->fSize.W/2 + a_oOther.GetBC().fRadius) * cos(i)),
//		a_oOther.GetBC().fCenter.Y + ((m_bbBoundingBox->fSize.H/2 + a_oOther.GetBC().fRadius) * sin(i)) };*/
//}

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
	m_glSurface = Graphics::LoadSurface<int>("Images/box1.png");
	m_glSurface->Layer = Graphics::LayerType::FOREGROUND;

	m_fPos = { 0, -175 };

	m_bbBoundingBox = Collision::NewBoundingBox(this, m_fPos, { (float)m_glSurface->OffsetD.W, (float)m_glSurface->OffsetD.H }, false, true);

	m_bMove = true;
	m_bUseGravity = true;

	auto temp1 = Graphics::LoadSurface<int>("Images/box1.png");
	temp1->Pos = { 0, 0 };
	temp1->Layer = Graphics::LayerType::FOREGROUND;
	temp1->OffsetD = { 1000, 100 };

	other.m_bbBoundingBox = Collision::NewBoundingBox(&other, { 0, 0 }, { (float)temp1->OffsetD.W, (float)temp1->OffsetD.H }, false, true);
}
Player::~Player()
{

}

