/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_MATRIX3X3
#define ELYSIUM_CORE_MATH_NUMERICS_MATRIX3X3

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#include "MathHelper.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_TYPETRAITS
#include "../Elysium.Core.Template/TypeTraits.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	template <typename T>
	class Matrix3x3 final
	{
	public:
		Matrix3x3(const T ValueM11, const  T ValueM12, const T ValueM13, const T ValueM21, const T ValueM22, const T ValueM23, 
			const T ValueM31, const T ValueM32, const T ValueM33);
		Matrix3x3(const Matrix3x3& Source);
		Matrix3x3(Matrix3x3&& Right) noexcept;
		~Matrix3x3();

		Matrix3x3<T>& operator=(const Matrix3x3& Source);
		Matrix3x3<T>& operator=(Matrix3x3&& Right) noexcept;

		T M11;
		T M12;
		T M13;

		T M21;
		T M22;
		T M23;

		T M31;
		T M32;
		T M33;

		//bool Decompose(Vector3Template<T>& Scale, QuaternionTemplate<T>& Rotation, Vector3Template<T>& Translation);
		//T Determinant();

		//static void Add();
	};

	template<class T>
	inline Matrix3x3<T>::Matrix3x3(const T ValueM11, const T ValueM12, const T ValueM13, const T ValueM21, const T ValueM22, const T ValueM23, 
		const T ValueM31, const T ValueM32, const T ValueM33)
		: M11(ValueM11), M12(ValueM12), M13(ValueM13), M21(ValueM21), M22(ValueM22), M23(ValueM23), M31(ValueM31), M32(ValueM32), M33(ValueM33)
	{ }
	template<typename T>
	inline Matrix3x3<T>::Matrix3x3(const Matrix3x3 & Source)
		: M11(Source.M11), M12(Source.M12), M13(Source.M13), M21(Source.M21), M22(Source.M22), M23(Source.M23),
			M31(Source.M31), M32(Source.M32), M33(Source.M33)
	{ }
	template<typename T>
	inline Matrix3x3<T>::Matrix3x3(Matrix3x3&& Right) noexcept
	{
		*this = Elysium::Core::Template::TypeTraits::Move(Right);
	}
	template<class T>
	inline Matrix3x3<T>::~Matrix3x3()
	{ }

	template<typename T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator=(const Matrix3x3 & Source)
	{
		if (this != &Source)
		{
			M11 = Source.M11;
			M12 = Source.M12;
			M13 = Source.M13;
			M21 = Source.M21;
			M22 = Source.M22;
			M23 = Source.M23;
			M31 = Source.M31;
			M32 = Source.M32;
			M33 = Source.M33;
		}
		return *this;
	}
	template<typename T>
	inline Matrix3x3<T>& Matrix3x3<T>::operator=(Matrix3x3&& Right) noexcept
	{
		if (this != &Right)
		{
			M11 = Elysium::Core::Template::TypeTraits::Move(Right.M11);
			M12 = Elysium::Core::Template::TypeTraits::Move(Right.M12);
			M13 = Elysium::Core::Template::TypeTraits::Move(Right.M13);
			M21 = Elysium::Core::Template::TypeTraits::Move(Right.M21);
			M22 = Elysium::Core::Template::TypeTraits::Move(Right.M22);
			M23 = Elysium::Core::Template::TypeTraits::Move(Right.M23);
			M31 = Elysium::Core::Template::TypeTraits::Move(Right.M31);
			M32 = Elysium::Core::Template::TypeTraits::Move(Right.M32);
			M33 = Elysium::Core::Template::TypeTraits::Move(Right.M33);
		}
		return *this;
	}
}
#endif
