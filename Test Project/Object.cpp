#include "Collision.h"

namespace Collision
{
	void Object::Handle()
	{
		Update();

		if (m_bMove)
			Move();

		UpdateBB();
	}
	void Object::LateHandle()
	{
		m_iPos = { (int)m_fPos.X, (int)m_fPos.Y };

		LateUpdate();
	}

	void Object::Update()
	{
		// Virtual, Do Nothing...
	}
	void Object::LateUpdate()
	{
		// Virtual, Do Nothing...
	}

	void Object::Move()
	{
		m_fPos += m_fVelocity;
		m_fPos += m_fAngularVel;
	}

	void Object::OnCollision(Object& a_oOther)
	{
		// Virtual, Do Nothing...
	}

	void Object::UpdateBB()
	{
		m_bbBoundingBox->fMin = { m_fPos.X - m_bbBoundingBox->fSize.W / 2, m_fPos.Y - m_bbBoundingBox->fSize.H / 2 };
		m_bbBoundingBox->fMax = { m_fPos.X + m_bbBoundingBox->fSize.W / 2, m_fPos.Y + m_bbBoundingBox->fSize.H / 2 };
	}

	const System::Point2D<float>& Object::GetPos()
	{
		return m_fPos;
	}
	const System::Point2D<int>& Object::GetIntPos()
	{
		return m_iPos;
	}

	const BoundingBox& Object::GetBoundingBox()
	{
		return *m_bbBoundingBox;
	}

	Object::Object()
	{
		m_fPos = { NULL, NULL };

		m_fVelocity = { NULL, NULL };
		m_fAngularVel = { NULL, NULL };

		m_bMove = false;

		m_bbBoundingBox = nullptr;
	}
	Object::~Object()
	{

	}
}