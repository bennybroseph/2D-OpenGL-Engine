#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#define PI 3.1415926535897932384626433832795

namespace System
{
	enum AngularDir
	{
		UP = 270,
		DOWN = 90,
		LEFT = 180,
		RIGHT = 0,

		UP_RIGHT = 315,
		UP_LEFT = 225,
		DOWN_RIGHT = 45,
		DOWN_LEFT = 135
	};

	template <typename T>
	struct Point2D
	{
		T X, Y;

		template <typename T, typename U>
		friend const Point2D<T> operator+(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB);
		template <typename T, typename U>
		friend const Point2D<T> operator-(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB);
		template <typename T>
		friend const Point2D<T> operator-(const Point2D<T>& ac_PointA);

		template <typename T, typename U>
		friend const Point2D<T> operator/(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB);
		
		template <typename T>
		friend const Point2D<T> operator/(const Point2D<T>& ac_PointA, const int ac_iNum);
	};
	template <typename T>
	struct Size2D
	{
		T W, H;

		template <typename T>
		friend const Size2D<T> operator/(const Size2D<T>& ac_SizeA, const int ac_iNum);

	};
	template <typename T>
	struct AngularVel
	{
		T Speed;
		T Angle;
	};
	template <typename T>
	struct Color
	{
		T Red, Blue, Green, Alpha;
	};


	template <typename T, typename U>
	const Point2D<T> operator+(const Point2D<T>& ac_PointA, const Size2D<U>& ac_SizeA);

	template <typename T, typename U>
	void operator+=(Point2D<T>& ac_PointA, const AngularVel<U>& ac_VelocityA);
}

namespace System
{
	template <typename T, typename U>
	const Point2D<T> operator+(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB)
	{
		const Point2D<T> PointC = { ac_PointA.X + ac_PointB.X, ac_PointA.Y + ac_PointB.Y };

		return PointC;
	}
	template <typename T>
	const Point2D<T> operator-(const Point2D<T>& ac_PointA)
	{
		const Point2D<T> PointC = { -ac_PointA.X, -ac_PointA.Y };

		return PointC;
	}
	template <typename T, typename U>
	const Point2D<T> operator-(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB)
	{
		return ac_PointA + (-ac_PointB);
	}
	template <typename T, typename U>
	const Point2D<T> operator/(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB)
	{
		const Point2D<T> PointC = { ac_PointA.X / ac_PointB.X, ac_PointA.Y / ac_PointB.Y };

		return PointC;
	}
	template <typename T>
	const Point2D<T> operator/(const Point2D<T>& ac_PointA, const int ac_iNum)
	{
		const Point2D<T> PointC = { ac_PointA.X / ac_iNum, ac_PointA.Y / ac_iNum };

		return PointC;
	}

	template <typename T>
	const Size2D<T> operator/(const Size2D<T>& ac_SizeA, const int ac_iNum)
	{
		const Size2D<T> SizeC = { ac_Dimension.W / ac_iNum, ac_Dimension.H / ac_iNum };

		return SizeC;
	}

	template <typename T, typename U>
	const Point2D<T> operator+(const Point2D<T>& ac_PointA, const Size2D<U>& ac_SizeA)
	{
		const Point2D<T> PointC = { ac_PointA.X + ac_SizeA.W, ac_PointA.Y + ac_SizeA.H };

		return PointC;
	}

	template <typename T, typename U>
	void operator+=(Point2D<T>& ac_PointA, const AngularVel<U>& ac_VelocityA)
	{
		ac_PointA = {
			ac_PointA.X + ac_VelocityA.Speed * (T)cos(ac_VelocityA.Angle * (PI / 180)),
			ac_PointA.Y + ac_VelocityA.Speed * (T)sin(ac_VelocityA.Angle * (PI / 180)) };
	}
}

#endif // _SYSTEM_H_
