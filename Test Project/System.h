#ifndef _SYSTEM_H_
#define _SYSTEM_H_

namespace System
{
	enum Direction
	{
		UP = 270,
		DOWN = 90,
		LEFT = 180,
		RIGHT = 0,

		UP_RIGHT = 315,
		UP_LEFT = 225,
		DOWN_RIGHT = 135,
		DOWN_LEFT = 45
	};

	template <typename T>
	struct Point2D
	{
		T X, Y;
	};
	template <typename T>
	struct Dimensions
	{
		T W, H;
	};
	template <typename T>
	struct Velocity
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
	const Point2D<T>& operator+(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB);
	template <typename T, typename U>
	const Point2D<T>& operator+(const Point2D<T>& ac_PointA, const Dimensions<U>& ac_Dimension);

	template <typename T, typename U>
	const Point2D<T>& operator-(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB);

	template <typename T, typename U>
	const Point2D<T>& operator/(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB);
	template <typename T, typename U>
	const Dimensions<T>& operator/(const Dimensions<T>& ac_Dimension, const int& ac_iNum);
	template <typename T>
	const Point2D<T>& operator/(const Point2D<T>& ac_PointA, const int& ac_iNum);

}

namespace System
{
	template <typename T, typename U>
	const Point2D<T>& operator+(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB)
	{
		const Point2D<T> PointC = { ac_PointA.X + ac_PointB.X, ac_PointA.Y + ac_PointB.Y };

		return PointC;
	}
	template <typename T, typename U>
	const Point2D<T>& operator+(const Point2D<T>& ac_PointA, const Dimensions<U>& ac_Dimension)
	{
		const Point2D<T> PointC = { ac_PointA.X + ac_Dimension.W, ac_PointA.Y + ac_Dimension.H };

		return PointC;
	}
	
	template <typename T, typename U>
	const Point2D<T>& operator-(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB)
	{
		const Point2D<T> PointC = { ac_PointA.X - ac_PointB.X, ac_PointA.Y - ac_PointB.Y };

		return PointC;
	}

	template <typename T, typename U>
	const Point2D<T>& operator/(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB)
	{
		const Point2D<T> PointC = { ac_PointA.X / ac_PointB.X, ac_PointA.Y / ac_PointB.Y };

		return PointC;
	}	
	template <typename T, typename U>
	const Dimensions<T>& operator/(const Dimensions<T>& ac_Dimension, const int& ac_iNum)
	{
		const Point2D<T> PointC = { ac_Dimension.W / ac_iNum, ac_Dimension.H / ac_iNum };

		return PointC;
	}
	template <typename T>
	const Point2D<T>& operator/(const Point2D<T>& ac_PointA, const int& ac_iNum)
	{
		const Point2D<T> PointC = { ac_PointA.X / ac_iNum, ac_PointA.Y / ac_iNum };

		return PointC;
	}
}

#endif // _SYSTEM_H_
