#ifndef _POINT2D_H_
#define _POINT2D_H_

namespace System
{
	// Defines a templated struct for an x and y point in 2D space as well as some overloaded operators to go along with it
	template <typename T>
	struct Point2D
	{
		T X, Y;

		// Addition of two 'Point2D's
		template <typename T, typename U>
		friend const Point2D<T> operator+(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB);
		// Subtraction of two 'Point2D's
		template <typename T, typename U>
		friend const Point2D<T> operator-(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB);
		// Applying a negative sign to a single Point2D; ex: "NegativeA = -PointA;"
		template <typename T>
		friend const Point2D<T> operator-(const Point2D<T>& ac_PointA);

		// Division of two 'Point2D's
		template <typename T, typename U>
		friend const Point2D<T> operator/(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB);

		// Division of a 'Point2D' and an integer; ex: "HalfofA = PointA / 2;"
		template <typename T, typename U>
		friend const Point2D<T> operator/(const Point2D<T>& ac_PointA, const U ac_iNum);

		template <typename T, typename U>
		friend void operator+=(Point2D<T>& ac_PointA, const Point2D<U> ac_PointB);
	};

	template <typename T, typename U>
	const Point2D<T> operator+(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB)
	{
		const Point2D<T> PointC = { ac_PointA.X + ac_PointB.X, ac_PointA.Y + ac_PointB.Y };

		return PointC;
	}
	template <typename T, typename U>
	const Point2D<T> operator-(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB)
	{
		return ac_PointA + (-ac_PointB);
	}
	template <typename T>
	const Point2D<T> operator-(const Point2D<T>& ac_PointA)
	{
		const Point2D<T> PointC = { -ac_PointA.X, -ac_PointA.Y };

		return PointC;
	}
	template <typename T, typename U>
	const Point2D<T> operator/(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB)
	{
		const Point2D<T> PointC = { ac_PointA.X / ac_PointB.X, ac_PointA.Y / ac_PointB.Y };

		return PointC;
	}
	template <typename T, typename U>
	const Point2D<T> operator/(const Point2D<T>& ac_PointA, const U ac_iNum)
	{
		const Point2D<T> PointC = { ac_PointA.X / ac_iNum, ac_PointA.Y / ac_iNum };

		return PointC;
	}

	template <typename T, typename U>
	void operator+=(Point2D<T>& ac_PointA, const Point2D<U> ac_PointB)
	{
		ac_PointA = { ac_PointA.X + ac_PointB.X, ac_PointA.Y + ac_PointB.Y };
	}
}

#endif // _POINT2D_H_
