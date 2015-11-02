#include "Enemy.h"



void Enemy::Update()
{
	m_fVelocity.X = -1;
}
void Enemy::LateUpdate()
{
	m_glSurface->Pos = m_iPos;
}

//void Enemy::OnBoxCollision(Object& a_oOther)
//{
//	if (m_fPrevPos.X - (m_bbBoundingBox->fSize.W / 2) >= a_oOther.GetBB().fMax.X)
//		m_fPos.X = a_oOther.GetBB().fMax.X + (m_bbBoundingBox->fSize.W / 2);
//	else if (m_fPrevPos.Y - (m_bbBoundingBox->fSize.H / 2) >= a_oOther.GetBB().fMax.Y)
//		m_fPos.Y = a_oOther.GetBB().fMax.Y + (m_bbBoundingBox->fSize.H / 2);
//
//	if (m_fPrevPos.X + (m_bbBoundingBox->fSize.W / 2) <= a_oOther.GetBB().fMin.X)
//		m_fPos.X = a_oOther.GetBB().fMin.X - (m_bbBoundingBox->fSize.W / 2);
//	else if (m_fPrevPos.Y + (m_bbBoundingBox->fSize.H / 2) <= a_oOther.GetBB().fMin.Y)
//		m_fPos.Y = a_oOther.GetBB().fMin.Y - (m_bbBoundingBox->fSize.H / 2);
//
//	UpdateBB();
//}

Enemy::Enemy()
{
	m_fPos = { float(-300 + rand() % 600), float(-600 + rand() % 500) };

	m_bMove = true;
	m_bUseGravity = true;

	m_glSurface = Graphics::LoadSurface<int>("Images/box1.png");
	m_glSurface->Pos = { (int)m_fPos.X, (int)m_fPos.Y };
	m_glSurface->Layer = Graphics::LayerType::FOREGROUND;
	m_glSurface->OffsetD = { 50, 50 };

	m_bbBoundingBox = Collision::NewBoundingBox(this, m_fPos, { (float)m_glSurface->OffsetD.W, (float)m_glSurface->OffsetD.H }, false, true);
}


Enemy::~Enemy()
{
}
