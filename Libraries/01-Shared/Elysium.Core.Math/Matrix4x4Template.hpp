/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_MATRIX4X4TEMPLATE
#define ELYSIUM_CORE_MATH_NUMERICS_MATRIX4X4TEMPLATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#include "MathHelper.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	template <typename T>
	class Matrix4x4Template
	{
	public:
		// constructors & destructor
		Matrix4x4Template(
			T ValueM11, T ValueM12, T ValueM13, T ValueM14,
			T ValueM21, T ValueM22, T ValueM23, T ValueM24,
			T ValueM31, T ValueM32, T ValueM33, T ValueM34,
			T ValueM41, T ValueM42, T ValueM43, T ValueM44);
		virtual ~Matrix4x4Template();

		// fields
		T M11;
		T M12;
		T M13;
		T M14;

		T M21;
		T M22;
		T M23;
		T M24;

		T M31;
		T M32;
		T M33;
		T M34;

		T M41;
		T M42;
		T M43;
		T M44;

		// methods
		//bool Decompose(Vector3Template<T>& Scale, QuaternionTemplate<T>& Rotation, Vector3Template<T>& Translation);
		//T Determinant();

		// static methods
		//static void Add();
	};

	template<class T>
	inline Matrix4x4Template<T>::Matrix4x4Template(
		T ValueM11, T ValueM12, T ValueM13, T ValueM14,
		T ValueM21, T ValueM22, T ValueM23, T ValueM24,
		T ValueM31, T ValueM32, T ValueM33, T ValueM34,
		T ValueM41, T ValueM42, T ValueM43, T ValueM44)
		: M11(ValueM11), M12(ValueM12), M13(ValueM13), M14(ValueM14),
		M21(ValueM21), M22(ValueM22), M23(ValueM23), M24(ValueM24),
		M31(ValueM31), M32(ValueM32), M33(ValueM33), M34(ValueM34),
		M41(ValueM41), M42(ValueM42), M43(ValueM43), M44(ValueM44)
	{
	}
	template<class T>
	inline Matrix4x4Template<T>::~Matrix4x4Template()
	{
	}
}
#endif
