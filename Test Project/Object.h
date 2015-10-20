#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "System.h"
#include "Graphics.h"

template <typename T>
class Object
{
protected:
	struct
	{
		System::Point2D<T> TopLeft, TopRight, BottomLeft, BottomRight;
	} m_BoundingBox;

	System::Point2D<T>	  m_Pos;
	System::Size2D<T>	  m_Size;
	System::AngularVel<T> m_Velocity;

	T Rotation;

	Graphics::GLSurface<T>* m_glSurface;

public:
	void Update();
	void LateUpdate();

	void UpdateBB();

	Object();
	virtual ~Object();
};
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
void Object<T>::UpdateBB()
{
	m_BoundingBox.TopLeft =		{ m_Pos.X - m_Size.W / 2, m_Pos.Y - m_Size.H / 2 };
	m_BoundingBox.TopRight =	{ m_Pos.X + m_Size.W / 2, m_Pos.Y - m_Size.H / 2 };
	m_BoundingBox.BottomLeft =	{ m_Pos.X - m_Size.W / 2, m_Pos.Y + m_Size.H / 2 };
	m_BoundingBox.BottomRight = { m_Pos.X + m_Size.W / 2, m_Pos.Y + m_Size.H / 2 };
}

template <typename T>
Object<T>::Object()
{
	m_Pos = { NULL, NULL };
	m_Size = { NULL, NULL };
	m_Velocity = { NULL, NULL };

	Rotation = NULL;

	m_BoundingBox.TopLeft =		{ NULL, NULL };
	m_BoundingBox.TopRight =	{ NULL, NULL };
	m_BoundingBox.BottomLeft =	{ NULL, NULL };
	m_BoundingBox.BottomRight = { NULL, NULL };

	m_glSurface = nullptr;
}
template <typename T>
Object<T>::~Object()
{
	// Virtual, Do Nothing...
}
#endif // _OBJECT_H_

