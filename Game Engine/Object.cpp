#include "Collision.h"



namespace Collision
{
	void Object::Handle()
	{
		Update();

		if (m_bUseGravity)
			m_fVelocity.Y += 0.8;

		if (m_bMove)
		{
			m_fPrevPos = m_fPos;
			Move();
		}

		UpdateBB();
		UpdateBC();
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
		/*struct DistanceHold
		{
			enum
			{
				TOP, BOTTOM, LEFT, RIGHT
			} Tag;
			float Distance;
		};

		std::vector<DistanceHold> Distances;

		Distances.push_back({ DistanceHold::LEFT, System::Distance<float, float>(m_fPrevPos,{ a_oOther.GetBB().fMin.X, a_oOther.GetBB().fMin.Y + a_oOther.GetBB().fSize.H / 2 }) });
		Distances.push_back({ DistanceHold::RIGHT, System::Distance<float, float>(m_fPrevPos,{ a_oOther.GetBB().fMax.X, a_oOther.GetBB().fMin.Y + a_oOther.GetBB().fSize.H / 2 }) });
		Distances.push_back({ DistanceHold::TOP, System::Distance<float, float>(m_fPrevPos,{ a_oOther.GetBB().fMin.X + a_oOther.GetBB().fSize.W / 2, a_oOther.GetBB().fMin.Y }) });
		Distances.push_back({ DistanceHold::BOTTOM, System::Distance<float, float>(m_fPrevPos,{ a_oOther.GetBB().fMin.X + a_oOther.GetBB().fSize.W / 2, a_oOther.GetBB().fMax.Y }) });

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
		case DistanceHold::TOP:
		{
			float b = -(m_fVelocity.Y / m_fVelocity.X) * m_fPos.X + m_fPos.Y;

			m_fPos.Y = a_oOther.GetBB().fMin.Y - (m_bbBoundingBox->fSize.H / 2);
			//m_fPos.X = (b - m_fPos.Y) / -(m_fVelocity.X / m_fVelocity.Y);

			break;
		}
		case DistanceHold::BOTTOM:
		{
			float b = -(m_fVelocity.Y / m_fVelocity.X) * m_fPos.X + m_fPos.Y;

			m_fPos.Y = a_oOther.GetBB().fMax.Y + (m_bbBoundingBox->fSize.H / 2);
			//m_fPos.X = (b - m_fPos.Y) / -(m_fVelocity.X / m_fVelocity.Y);

			break;
		}
		case DistanceHold::LEFT:
		{
			float b = -(m_fVelocity.Y / m_fVelocity.X) * m_fPos.X + m_fPos.Y;

			m_fPos.X = a_oOther.GetBB().fMin.X - (m_bbBoundingBox->fSize.W / 2);
			//m_fPos.Y = (m_fVelocity.Y / m_fVelocity.X) * m_fPos.X + b;

			break;
		}
		case DistanceHold::RIGHT:
		{
			float b = -(m_fVelocity.Y / m_fVelocity.X) * m_fPos.X + m_fPos.Y;

			m_fPos.X = a_oOther.GetBB().fMax.X + (m_bbBoundingBox->fSize.W / 2);
			//m_fPos.Y = (m_fVelocity.Y / m_fVelocity.X) * m_fPos.X + b;

			break;
		}
		}*/
		if (&a_oOther.GetBB() != nullptr)
			OnBoxCollision(a_oOther);
		/*if (&a_oOther.GetBC() != nullptr)
			OnCircleCollision(a_oOther);*/
	}
	//void Object::OnCircleCollision(Object& a_oOther)
	//{
	//	// Virtual, Do Nothing...
	//}
	void Object::OnBoxCollision(Object& a_oOther)
	{
		// Collision with left side of other object
		if (m_fPrevPos.X - (m_bbBoundingBox->fSize.W / 2) >= a_oOther.GetBB().fMax.X)
		{
			m_fPos.X = a_oOther.GetBB().fMax.X + (m_bbBoundingBox->fSize.W / 2);
			m_fVelocity.X = 0;
		}
		else if (m_fPrevPos.Y - (m_bbBoundingBox->fSize.H / 2) >= a_oOther.GetBB().fMax.Y)
		{
			m_fPos.Y = a_oOther.GetBB().fMax.Y + (m_bbBoundingBox->fSize.H / 2);
			m_fVelocity.Y = 0;
		}

		// Collision with right side of other object
		else if (m_fPrevPos.X + (m_bbBoundingBox->fSize.W / 2) <= a_oOther.GetBB().fMin.X)
		{
			m_fPos.X = a_oOther.GetBB().fMin.X - (m_bbBoundingBox->fSize.W / 2);
			m_fVelocity.X = 0;
		}
		else if (m_fPrevPos.Y + (m_bbBoundingBox->fSize.H / 2) <= a_oOther.GetBB().fMin.Y)
		{
			m_fPos.Y = a_oOther.GetBB().fMin.Y - (m_bbBoundingBox->fSize.H / 2);
			m_fVelocity.Y = 0;
		}
		else
		{
			if (m_fPos.X - (m_bbBoundingBox->fSize.W / 2) >= a_oOther.GetBB().fMin.X)
			{
				m_fPos.X = a_oOther.GetBB().fMax.X + (m_bbBoundingBox->fSize.W / 2);
				m_fVelocity.X = 0;
			}
			else if (m_fPos.Y - (m_bbBoundingBox->fSize.H / 2) >= a_oOther.GetBB().fMin.Y)
			{
				m_fPos.Y = a_oOther.GetBB().fMax.Y + (m_bbBoundingBox->fSize.H / 2);
				m_fVelocity.Y = 0;
			}
			//m_fPrevPos -= m_fVelocity;
			//OnBoxCollision(a_oOther);
		}


		UpdateBB();
	}

	void Object::UpdateBB()
	{
		if (m_bbBoundingBox != nullptr)
		{
			m_bbBoundingBox->fMin = { m_fPos.X - m_bbBoundingBox->fSize.W / 2, m_fPos.Y - m_bbBoundingBox->fSize.H / 2 };
			m_bbBoundingBox->fMax = { m_fPos.X + m_bbBoundingBox->fSize.W / 2, m_fPos.Y + m_bbBoundingBox->fSize.H / 2 };
		}
	}

	void Object::UpdateBC()
	{
		/*if (m_bcBoundingCircle != nullptr)
		{
			m_bcBoundingCircle->fCenter = m_fPos;
		}*/
	}

	const System::Point2D<float>& Object::GetPos()
	{
		return m_fPos;
	}
	const System::Point2D<int>& Object::GetIntPos()
	{
		return m_iPos;
	}

	const BoundingBox& Object::GetBB()
	{
		return *m_bbBoundingBox;
	}

	/*const BoundingCircle& Object::GetBC()
	{
		return *m_bcBoundingCircle;
	}*/

	Object::Object()
	{
		m_fPos = { NULL, NULL };

		m_fVelocity = { NULL, NULL };
		m_fAngularVel = { NULL, NULL };

		m_bMove = false;

		m_bbBoundingBox = nullptr;
		/*m_bcBoundingCircle = nullptr;*/
	}
	Object::~Object()
	{

	}
}