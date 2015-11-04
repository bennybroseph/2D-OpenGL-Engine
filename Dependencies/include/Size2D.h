#ifndef _SIZE2D_H_
#define _SIZE2D_H_

namespace System
{
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
}

namespace System
{
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
}

#endif // _SIZE2D_H_