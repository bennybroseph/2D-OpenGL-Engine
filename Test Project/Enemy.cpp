#include "Enemy.h"



void Enemy::Update()
{
	m_fVelocity = { float(-5 + rand() % 11), float(-5 + rand() % 11) };
}
void Enemy::LateUpdate()
{
	m_glSurface->Pos = m_iPos;
}

Enemy::Enemy()
{
	m_fPos = { float(-400 + rand() % 800), float(-400 + rand() % 300) };

	m_bMove = true;
	m_bUseGravity = false;

	m_glSurface = Graphics::LoadSurface<int>("Images/box1.png");
	m_glSurface->Pos = { (int)m_fPos.X, (int)m_fPos.Y };
	m_glSurface->Layer = Graphics::LayerType::FOREGROUND;
	m_glSurface->OffsetD = { 20, 20 };

	m_bbBoundingBox = Collision::NewBoundingBox(this, m_fPos, { (float)m_glSurface->OffsetD.W, (float)m_glSurface->OffsetD.H }, false, true);
}

Enemy::~Enemy()
{
}
