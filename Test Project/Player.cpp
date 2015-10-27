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

void Player::Draw()
{
	System::Point2D<float> Center = { 800, 450 };
}

void Player::OnBoxCollision(Object& a_oOther)
{
	struct DistanceHold
	{
		enum
		{
			TOP, BOTTOM, LEFT, RIGHT
		} Tag;
		float Distance;
	};

	std::vector<DistanceHold> Distances;

	Distances.push_back({ DistanceHold::LEFT, System::Distance<float, float>(m_fPrevPos, { a_oOther.GetBB().fMin.X, a_oOther.GetBB().fMin.Y + a_oOther.GetBB().fSize.H / 2 }) });
	Distances.push_back({ DistanceHold::RIGHT, System::Distance<float, float>(m_fPrevPos, { a_oOther.GetBB().fMax.X, a_oOther.GetBB().fMin.Y + a_oOther.GetBB().fSize.H / 2 }) });
	Distances.push_back({ DistanceHold::TOP, System::Distance<float, float>(m_fPrevPos, { a_oOther.GetBB().fMin.X + a_oOther.GetBB().fSize.W / 2, a_oOther.GetBB().fMin.Y }) });
	Distances.push_back({ DistanceHold::BOTTOM, System::Distance<float, float>(m_fPrevPos, { a_oOther.GetBB().fMin.X + a_oOther.GetBB().fSize.W / 2, a_oOther.GetBB().fMax.Y }) });

	int i = 1;
	while (Distances.size() > 1)
	{

		if (Distances[0].Distance < Distances[i].Distance)
		{
			Distances.erase(Distances.begin() + i);
			i = 1;
		}
		else
		{
			Distances.erase(Distances.begin());
			i = 1;
		}
	}

	switch (Distances[0].Tag)
	{
	case DistanceHold::TOP:	   m_fPos.Y = a_oOther.GetBB().fMin.Y - (m_bbBoundingBox->fSize.H / 2); break;
	case DistanceHold::BOTTOM: m_fPos.Y = a_oOther.GetBB().fMax.Y + (m_bbBoundingBox->fSize.H / 2); break;
	case DistanceHold::LEFT:   m_fPos.X = a_oOther.GetBB().fMin.X - (m_bbBoundingBox->fSize.W / 2); break;
	case DistanceHold::RIGHT:  m_fPos.X = a_oOther.GetBB().fMax.X + (m_bbBoundingBox->fSize.W / 2); break;
	}
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

	m_bbBoundingBox = Collision::NewBoundingBox(this, m_fPos, { (float)m_glSurface->OffsetD.W, (float)m_glSurface->OffsetD.H }, false, true);

	m_fPos = { 200, 200 };

	auto temp1 = Graphics::LoadSurface<int>("Images/circle1.png");
	temp1->Pos = { 0, 0 };
	temp1->Layer = Graphics::LayerType::FOREGROUND;

	other.m_bcBoundingCircle = Collision::NewBoundingCircle(&other, { 0, 0 }, (float)m_glSurface->OffsetD.W / 2, false, true);
}
Player::~Player()
{

}

