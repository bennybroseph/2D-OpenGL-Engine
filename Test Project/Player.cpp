#include "Player.h"

const float SPEED = 10;

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
	other2.UpdateBB();
}

void Player::Draw()
{
	System::Point2D<float> Center = { 800, 450 };
}

void Player::OnBoxCollision(Object& a_oOther)
{
	if (m_fPrevPos.X - (m_bbBoundingBox->fSize.W / 2) >= a_oOther.GetBB().fMax.X)
		m_fPos.X = a_oOther.GetBB().fMax.X + (m_bbBoundingBox->fSize.W / 2);
	else if (m_fPrevPos.Y - (m_bbBoundingBox->fSize.H / 2) >= a_oOther.GetBB().fMax.Y)
		m_fPos.Y = a_oOther.GetBB().fMax.Y + (m_bbBoundingBox->fSize.H / 2);

	if(m_fPrevPos.X + (m_bbBoundingBox->fSize.W / 2) <= a_oOther.GetBB().fMin.X)
		m_fPos.X = a_oOther.GetBB().fMin.X - (m_bbBoundingBox->fSize.W / 2);
	else if (m_fPrevPos.Y + (m_bbBoundingBox->fSize.H / 2) <= a_oOther.GetBB().fMin.Y)
		m_fPos.Y = a_oOther.GetBB().fMin.Y - (m_bbBoundingBox->fSize.H / 2);

	UpdateBB();
}
void Player::OnCircleCollision(Object& a_oOther)
{
	printf("Collision! ");
	/*auto i = atan2f(m_fPrevPos.Y - a_oOther.GetBC().fCenter.Y, m_fPrevPos.X - a_oOther.GetBC().fCenter.X);
	m_fPos = {
		a_oOther.GetBC().fCenter.X + ((m_bbBoundingBox->fSize.W/2 + a_oOther.GetBC().fRadius) * cos(i)),
		a_oOther.GetBC().fCenter.Y + ((m_bbBoundingBox->fSize.H/2 + a_oOther.GetBC().fRadius) * sin(i)) };*/
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
	m_glSurface = Graphics::LoadSurface<int>("Images/box1.png");
	m_glSurface->Layer = Graphics::LayerType::FOREGROUND;
	
	m_fPos = { 75, 75 };
	
	m_bbBoundingBox = Collision::NewBoundingBox(this, m_fPos, { (float)m_glSurface->OffsetD.W, (float)m_glSurface->OffsetD.H }, false, true);

	auto temp1 = Graphics::LoadSurface<int>("Images/box1.png");
	temp1->Pos = { 0, 0 };
	temp1->Layer = Graphics::LayerType::FOREGROUND;
	temp1->OffsetD = { 200, 100 };

	other.m_bbBoundingBox = Collision::NewBoundingBox(&other, { 0, 0 }, { (float)temp1->OffsetD.W, (float)temp1->OffsetD.H }, false, true);

	other2.m_fPos = { -75, -75 };

	auto temp2 = Graphics::LoadSurface<int>("Images/box1.png");
	temp2->Pos = { (int)other2.m_fPos.X, (int)other2.m_fPos.Y };
	temp2->Layer = Graphics::LayerType::FOREGROUND;
	temp2->OffsetD = { 50, 50 };

	other2.m_bbBoundingBox = Collision::NewBoundingBox(&other2, other2.m_fPos, { (float)temp2->OffsetD.W, (float)temp2->OffsetD.H }, false, true);
}
Player::~Player()
{

}

