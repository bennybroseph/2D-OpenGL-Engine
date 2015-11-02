#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#define PI 3.1415926535897932384626433832795 // PI in such a way that anything that includes "System.h" can use it

namespace System
{
	// Holds a quick reference to appropriate angles for d-pad based movement
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
	};

	// Defines a templated struct for dimensions/size in 2D space as well as some overloaded operators to go along with it
	template <typename T>
	struct Size2D
	{
		T W, H;

		template <typename T, typename U>
		friend const Size2D<T> operator/(const Size2D<T>& ac_SizeA, const U ac_iNum);
		template <typename T, typename U>
		friend const Size2D<T> operator*(const Size2D<T>& ac_SizeA, const U ac_iNum);
	};
	// Defines a templated struct for angular velocity in 2D space
	template <typename T>
	struct AngularVel
	{
		T Speed;
		T Angle;
	};
	template <typename T>
	struct Velocity2D
	{
		T X, Y;

		template <typename T, typename U>
		friend const Velocity2D<T> operator+(const Velocity2D<T>& ac_VelocityA, const Velocity2D<T>& ac_VelocityB);
		template <typename T, typename U>
		friend const Velocity2D<T> operator-(const Velocity2D<T>& ac_VelocityA, const Velocity2D<T>& ac_VelocityB);
		template <typename T>
		friend const Velocity2D<T> operator-(const Velocity2D<T>& ac_VelocityA);

		template <typename T, typename U>
		friend const Velocity2D<T> operator*(const T ac_Num, const Velocity2D<U>& ac_VelocityA);
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
	const AngularVel<T> CalculateAngular(const Velocity2D<T>& ac_VelocityA, const U ac_iSpeed = 1);
	template <typename T, typename U>
	void ToAngular(Velocity2D<T>& ac_VelocityA, const U ac_iSpeed = 1);

	template <typename T, typename U>
	const T Distance(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB);
}

namespace System
{
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
	const Size2D<T> operator/(const Size2D<T>& ac_SizeA, const U ac_iNum)
	{
		const Size2D<T> SizeC = { ac_Dimension.W / ac_iNum, ac_Dimension.H / ac_iNum };

		return SizeC;
	}
	template <typename T, typename U>
	const Size2D<T> operator*(const Size2D<T>& ac_SizeA, const U ac_iNum)
	{
		const Size2D<T> SizeC = { ac_Dimension.W * ac_iNum, ac_Dimension.H * ac_iNum };

		return SizeC;
	}

	template <typename T, typename U>
	const Velocity2D<T> operator+(const Velocity2D<T>& ac_VelocityA, const Velocity2D<U>& ac_VelocityB)
	{
		const Velocity2D<T> VelocityC = { ac_VelocityA.X + ac_VelocityB.X, ac_VelocityA.Y + ac_VelocityB.Y };

		return VelocityC;
	}
	template <typename T, typename U>
	const Velocity2D<T> operator-(const Velocity2D<T>& ac_VelocityA, const Velocity2D<T>& ac_VelocityB)
	{
		return ac_VelocityA + (-ac_VelocityB);
	}
	template <typename T>
	const Velocity2D<T> operator-(const Velocity2D<T>& ac_VelocityA)
	{
		const Velocity2D<T> VelocityC = { -ac_VelocityA.X, -ac_VelocityA.Y };

		return VelocityC;
	}

	template <typename T, typename U>
	const Velocity2D<T> operator*(const T ac_Num, const Velocity2D<U>& ac_VelocityA)
	{
		const Velocity2D<T> VelocityC = { ac_Num * ac_VelocityA.X, ac_Num * ac_VelocityA.Y };

		return VelocityC;
	}

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
	void ToAngular(Velocity2D<T>& a_VelocityA, const U ac_iSpeed)
	{
		if (a_VelocityA.X != 0 || a_VelocityA.Y != 0)
		{
			const AngularVel<T> VelocityC = { ac_iSpeed, atan2(a_VelocityA.Y, a_VelocityA.X) * (180 / PI) };
			
			a_VelocityA = {
				(a_VelocityA.X != 0) ? VelocityC.Speed * (T)cos(VelocityC.Angle * (PI / 180)) : 0,
				(a_VelocityA.Y != 0) ? VelocityC.Speed * (T)sin(VelocityC.Angle * (PI / 180)) : 0};
		}
		else
			return;
	}

	template <typename T, typename U>
	const T Distance(const Point2D<T>& ac_PointA, const Point2D<U>& ac_PointB)
	{
		const T Distance = sqrt(pow(ac_PointB.X - ac_PointA.X, 2) + pow(ac_PointB.Y - ac_PointA.Y, 2));

		return Distance;
	}
}

#endif // _SYSTEM_H_
