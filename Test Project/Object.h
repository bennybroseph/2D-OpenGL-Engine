#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "Collision.h"

namespace Collision
{
	template <typename T>
	class Object
	{
	protected:
		System::Point2D<T>	  m_Pos;
		System::Size2D<T>	  m_Size;
		System::AngularVel<T> m_Velocity;

		T m_Rotation;

		bool m_bMove, m_bRotate;
		bool m_bUseGravity;

		Graphics::GLSurface<T>* m_glSurface;
		BoundingBox<T>* m_bbBoundingBox;

	public:
		void Handle();
		void LateHandle();

		virtual void Update();
		virtual void LateUpdate();

		virtual void Move();

		virtual void UpdateBB();

		virtual void OnCollision(Object<T>& a_oOther);

		const System::Point2D<T>& GetPos();

		Object();
		virtual ~Object();
	};
	template <typename T>
	void Object<T>::Handle()
	{
		Update();

		if (m_bMove)
			Move();
	}
	template <typename T>
	void Object<T>::LateHandle()
	{
		LateUpdate();

		UpdateBB();
		m_glSurface->Pos = m_Pos;

		printf("%d : %d \n", m_Pos.X, m_Pos.Y);
	}

	template <typename T>
	void Object<T>::Update()
	{
		// Virtual, Do Nothing...
	}
	template <typename T>
	void Object<T>::LateUpdate()
	{
		// Virtual, Do Nothing...
	}

	template <typename T>
	void Object<T>::Move()
	{
		m_Pos += m_Velocity;
	}

	template <typename T>
	void Object<T>::UpdateBB()
	{
		m_bbBoundingBox->Min = { m_Pos.X - m_Size.W / 2, m_Pos.Y - m_Size.H / 2 };
		m_bbBoundingBox->Max = { m_Pos.X + m_Size.W / 2, m_Pos.Y + m_Size.H / 2 };
	}

	template <typename T>
	void Object<T>::OnCollision(Object<T>& a_oOther)
	{

	}

	template <typename T>
	const System::Point2D<T>& Object<T>::GetPos()
	{
		return m_Pos;
	}

	template <typename T>
	Object<T>::Object()
	{
		m_Pos = { NULL, NULL };
		m_Size = { NULL, NULL };
		m_Velocity = { NULL, NULL };

		m_Rotation = NULL;

		m_bMove = false;
		m_bRotate = false;

		m_bUseGravity = false;

		m_bbBoundingBox = nullptr;

		m_glSurface = nullptr;
	}
	template <typename T>
	Object<T>::~Object()
	{
		// Virtual, Do Nothing...
	}
}

#endif // _OBJECT_H_