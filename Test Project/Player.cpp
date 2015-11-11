#include "Player.h"

const float SPEED = 5;

const float SEGMENT_DIVISION = 25;
const float SEGMENT_LENGTH = 15;

const System::Point2D<float> GRAPH_ORIGIN = { 800, 450 };

void Player::Update()
{
	if (m_bUp || m_bDown || m_bLeft || m_bRight)
	{
		m_fVelocity = { 0, 0 };
		m_fVelocity.X = 0;

		if (m_bUp)
			m_fVelocity.Y += -SPEED;
		if (m_bDown)
			m_fVelocity.Y += SPEED;

		if (m_bLeft)
			m_fVelocity.X += -SPEED;
		if (m_bRight)
			m_fVelocity.X += SPEED;

		System::ToAngular(m_fVelocity, SPEED);
	}
	else
	{
		m_fVelocity = { 0, 0 };
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
	//System::Size2D<float> Test = (System::Size2D<float>)Center;

	//Graphics::DrawLine(m_fPos + Center, (m_fPos + Center) + (50.0f * m_fVelocity), { 255, 255, 255, 255 });

	Graphics::DrawLine({ GRAPH_ORIGIN.X, 0 }, { GRAPH_ORIGIN.X, 900 }, { 255, 255, 255, 255 });
	Graphics::DrawLine({ 0, GRAPH_ORIGIN.Y }, { 1600, GRAPH_ORIGIN.Y }, { 255, 255, 255, 255 });

	for (float i = 1; i < 1600 / SEGMENT_DIVISION; ++i)
	{
		Graphics::DrawLine({ GRAPH_ORIGIN.X + i * SEGMENT_DIVISION, GRAPH_ORIGIN.Y - SEGMENT_LENGTH }, { GRAPH_ORIGIN.X + i * SEGMENT_DIVISION, GRAPH_ORIGIN.Y + SEGMENT_LENGTH }, { 255, 255, 255, 255 });
		Graphics::DrawLine({ GRAPH_ORIGIN.X - i * SEGMENT_DIVISION, GRAPH_ORIGIN.Y - SEGMENT_LENGTH }, { GRAPH_ORIGIN.X - i * SEGMENT_DIVISION, GRAPH_ORIGIN.Y + SEGMENT_LENGTH }, { 255, 255, 255, 255 });
	}
	for (float i = 1; i < 900 / SEGMENT_DIVISION; ++i)
	{
		Graphics::DrawLine({ GRAPH_ORIGIN.X - SEGMENT_LENGTH, GRAPH_ORIGIN.Y + i * SEGMENT_DIVISION }, { GRAPH_ORIGIN.X + SEGMENT_LENGTH, GRAPH_ORIGIN.Y + i * SEGMENT_DIVISION }, { 255, 255, 255, 255 });
		Graphics::DrawLine({ GRAPH_ORIGIN.X - SEGMENT_LENGTH, GRAPH_ORIGIN.Y - i * SEGMENT_DIVISION }, { GRAPH_ORIGIN.X + SEGMENT_LENGTH, GRAPH_ORIGIN.Y - i * SEGMENT_DIVISION }, { 255, 255, 255, 255 });
	}
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
	m_glSurface->Layer = Graphics::LayerType::ALWAYS_TOP;

	m_fPos = { 0, -175 };

	m_bbBoundingBox = Collision::NewBoundingBox(this, m_fPos, { (float)m_glSurface->OffsetSize.W, (float)m_glSurface->OffsetSize.H }, false, true);

	m_bMove = true;
	m_bUseGravity = false;

	auto temp1 = Graphics::LoadSurface<int>("Images/box1.png");
	temp1->Pos = { 0, 0 };
	temp1->Layer = Graphics::LayerType::FOREGROUND;
	temp1->OffsetSize = { 1000, 100 };

	other.m_bbBoundingBox = Collision::NewBoundingBox(&other, { 0, 0 }, { (float)temp1->OffsetSize.W, (float)temp1->OffsetSize.H }, false, false);
}
Player::~Player()
{

}

