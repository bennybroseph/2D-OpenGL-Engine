#ifndef _VELOCITY2D_H_
#define _VELOCITY2D_H_

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

	template <typename T, typename U>
	void ToAngular(Velocity2D<T>& ac_VelocityA, const U ac_Speed = 1);
	template <typename T, typename U, typename V>
	void ToAngular(Velocity2D<T>& ac_VelocityA, const U ac_Angle, const V ac_Speed = 1);
}

namespace System
{
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
}

namespace System
{
	template <typename T, typename U>
	void ToAngular(Velocity2D<T>& a_VelocityA, const U ac_Speed)
	{
		if (a_VelocityA.X != 0 || a_VelocityA.Y != 0)
		{
			const U Angle = (U)(atan2(a_VelocityA.Y, a_VelocityA.X) * (180 / PI));

			a_VelocityA = {
				(a_VelocityA.X != 0) ? ac_Speed * (T)cos(Angle * (PI / 180)) : 0,
				(a_VelocityA.Y != 0) ? ac_Speed * (T)sin(Angle * (PI / 180)) : 0 };
		}
		else
			return;
	}
	template <typename T, typename U, typename V>
	void ToAngular(Velocity2D<T>& ac_VelocityA, const U ac_Angle, const V ac_Speed)
	{
		a_VelocityA = {
			(a_VelocityA.X != 0) ? ac_Speed * (T)cos(ac_Angle * (PI / 180)) : 0,
			(a_VelocityA.Y != 0) ? ac_Speed * (T)sin(ac_Angle * (PI / 180)) : 0 };
	}
}

#endif // _VELOCITY2D_H_
