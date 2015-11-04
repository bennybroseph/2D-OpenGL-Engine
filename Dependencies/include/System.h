#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "Point2D.h"
#include "Size2D.h"
#include "Velocity2D.h"

namespace System
{	
	// Defines a templated struct for angular velocity in 2D space
	template <typename T>
	struct AngularVel
	{
		T Speed;
		T Angle;
	};
	
	// Defines a templated struct for color in the format rgba, which is the most useful for OpenGL
	// Accepted value range is 0 - 255
	template <typename T>
	struct Color
	{
		T Red, Green, Blue, Alpha;
	};

	// Defines what it means to add a 'Point2D' and a 'Size2D'
	template <typename T, typename U>
	const Point2D<T> operator+(const Point2D<T>& ac_PointA, const Size2D<U>& ac_SizeA);

	template <typename T, typename U>
	const Point2D<T> operator+(const Point2D<T>& ac_PointA, const Velocity2D<U>& ac_VelocityA);
	template <typename T, typename U>
	const Point2D<T> operator-(const Point2D<T>& ac_PointA, const Velocity2D<U>& ac_VelocityA);
	// Defines what it means to set a 'Point2D' equal to itself + an 'AngularVel'
	template <typename T, typename U>
	void operator+=(Point2D<T>& ac_PointA, const AngularVel<U>& ac_VelocityA);
	// Defines what it means to set a 'Point2D' equal to itself + an 'Velocity'
	template <typename T, typename U>
	void operator+=(Point2D<T>& ac_PointA, const Velocity2D<U>& ac_VelocityA);
	template <typename T, typename U>
	void operator-=(Point2D<T>& ac_PointA, const Velocity2D<U>& ac_VelocityA);

	template <typename T, typename U>
	const AngularVel<T> CalculateAngular(const Velocity2D<T>& ac_VelocityA, const U ac_iSpeed);

	template <typename T, typename U>
	const T Distance(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB);
}

namespace System
{
	template <typename T, typename U>
	const Point2D<T> operator+(const Point2D<T>& ac_PointA, const Size2D<U>& ac_SizeA)
	{
		const Point2D<T> PointC = { ac_PointA.X + ac_SizeA.W, ac_PointA.Y + ac_SizeA.H };

		return PointC;
	}

	template <typename T, typename U>
	const Point2D<T> operator+(const Point2D<T>& ac_PointA, const Velocity2D<U>& ac_VelocityA)
	{
		const Point2D<T> PointC = { ac_PointA.X + ac_VelocityA.X, ac_PointA.Y + ac_VelocityA.Y };

		return PointC;
	}
	template <typename T, typename U>
	const Point2D<T> operator-(const Point2D<T>& ac_PointA, const Velocity2D<U>& ac_VelocityA)
	{
		return ac_PointA + (-ac_VelocityA);
	}
	template <typename T, typename U>
	void operator+=(Point2D<T>& ac_PointA, const AngularVel<U>& ac_VelocityA)
	{
		ac_PointA = {
			ac_PointA.X + ac_VelocityA.Speed * (T)cos(ac_VelocityA.Angle * (PI / 180)),
			ac_PointA.Y + ac_VelocityA.Speed * (T)sin(ac_VelocityA.Angle * (PI / 180)) };
	}

	template <typename T, typename U>
	void operator+=(Point2D<T>& ac_PointA, const Velocity2D<U>& ac_VelocityA)
	{
		ac_PointA = { ac_PointA.X + ac_VelocityA.X, ac_PointA.Y + ac_VelocityA.Y};
	}
	template <typename T, typename U>
	void operator-=(Point2D<T>& ac_PointA, const Velocity2D<U>& ac_VelocityA)
	{
		ac_PointA += -ac_VelocityA;
	}

	template <typename T, typename U>
	const AngularVel<T> CalculateAngular(const Velocity2D<T>& ac_VelocityA, const U ac_iSpeed)
	{
		if (ac_VelocityA.X != 0 || ac_VelocityA.Y != 0)
		{
			const AngularVel<T> VelocityC = { ac_iSpeed, atan2(ac_VelocityA.Y, ac_VelocityA.X) * (180 / PI) };

			return VelocityC;
		}
		else
			return{ 0, 0 };
	}

	template <typename T, typename U>
	const T Distance(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB)
	{
		const T Distance = sqrt(pow(ac_PointB.X - ac_PointA.X, 2) + pow(ac_PointB.Y - ac_PointA.Y, 2));

		return Distance;
	}
}

#endif // _SYSTEM_H_
