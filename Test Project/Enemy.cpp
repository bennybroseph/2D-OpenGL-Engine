#include "Enemy.h"



void Enemy::Update()
{
	
}
void Enemy::LateUpdate()
{
	m_glPlayerSprite->SetPos(m_iPos);
	m_glPlayerSprite->Update();
}

Enemy::Enemy()
{
	m_fPos = { float(-400 + rand() % 800), float(-400 + rand() % 300) };

	m_bMove = true;
	m_bUseGravity = false;

	m_glPlayerSprite = new GLSprite<int>("Images/My-Eyes.png", { 300, 238 }, { 0, 0 }, { 31, 0 }, 0.03f);
	m_glPlayerSprite->SetLayer(Graphics::LayerType::FOREGROUND);
	//m_glSurface->Pos = { (int)m_fPos.X, (int)m_fPos.Y };
	//m_glSurface->Layer = Graphics::LayerType::FOREGROUND;
	//m_glSurface->OffsetSize = { 20, 20 };

	m_fVelocity = { float(-250 + rand() % 500), float(-250 + rand() % 500) };

	m_bbBoundingBox = Collision::NewBoundingBox(this, m_fPos, { 300.0f, 238.0f }, false, true);
}

Enemy::~Enemy()
{
}
