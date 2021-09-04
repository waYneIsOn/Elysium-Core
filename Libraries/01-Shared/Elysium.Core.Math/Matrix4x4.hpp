/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_MATRIX4X4
#define ELYSIUM_CORE_MATH_NUMERICS_MATRIX4X4

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#include "MathHelper.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	template <typename T>
	class Matrix4x4 final
	{
	public:
		Matrix4x4(const T ValueM11, const T ValueM12, const T ValueM13, const T ValueM14, const T ValueM21, const T ValueM22, const T ValueM23, const T ValueM24,
			const T ValueM31, const T ValueM32, const T ValueM33, const T ValueM34, const T ValueM41, const T ValueM42, const T ValueM43, const T ValueM44);
		Matrix4x4(const Matrix4x4& Source);
		Matrix4x4(Matrix4x4&& Right) noexcept;
		~Matrix4x4();

		Matrix4x4<T>& operator=(const Matrix4x4& Source);
		Matrix4x4<T>& operator=(Matrix4x4&& Right) noexcept;

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

		//bool Decompose(Vector3Template<T>& Scale, QuaternionTemplate<T>& Rotation, Vector3Template<T>& Translation);
		//T Determinant();

		//static void Add();
	};

	template<class T>
	inline Matrix4x4<T>::Matrix4x4(const T ValueM11, const T ValueM12, const T ValueM13, const T ValueM14, 
		const T ValueM21, const T ValueM22, const T ValueM23, const T ValueM24,
		const T ValueM31, const T ValueM32, const T ValueM33, const T ValueM34,
		const T ValueM41, const T ValueM42, const T ValueM43, const T ValueM44)
		: M11(ValueM11), M12(ValueM12), M13(ValueM13), M14(ValueM14), M21(ValueM21), M22(ValueM22), M23(ValueM23), M24(ValueM24),
		M31(ValueM31), M32(ValueM32), M33(ValueM33), M34(ValueM34), M41(ValueM41), M42(ValueM42), M43(ValueM43), M44(ValueM44)
	{ }
	template<typename T>
	inline Matrix4x4<T>::Matrix4x4(const Matrix4x4 & Source)
		: M11(Source.M11), M12(Source.M12), M13(Source.M13), M14(Source.M14), M21(Source.M21), M22(Source.M22), M23(Source.M23), M24(Source.M24),
		M31(Source.M31), M32(Source.M32), M33(Source.M33), M34(Source.M34), M41(Source.M41), M42(Source.M42), M43(Source.M43), M44(Source.M44)
	{ }
	template<typename T>
	inline Matrix4x4<T>::Matrix4x4(Matrix4x4&& Right) noexcept
	{
		*this = Elysium::Core::Template::Move(Right);
	}
	template<class T>
	inline Matrix4x4<T>::~Matrix4x4()
	{ }

	template<typename T>
	inline Matrix4x4<T>& Matrix4x4<T>::operator=(const Matrix4x4 & Source)
	{
		if (this != &Source)
		{
			M11 = Source.M11;
			M12 = Source.M12;
			M13 = Source.M13;
			M14 = Source.M14;
			M21 = Source.M21;
			M22 = Source.M22;
			M23 = Source.M23;
			M24 = Source.M24;
			M31 = Source.M31;
			M32 = Source.M32;
			M33 = Source.M33;
			M34 = Source.M34;
			M41 = Source.M41;
			M42 = Source.M42;
			M43 = Source.M43;
			M44 = Source.M44;
		}
		return *this;
	}
	template<typename T>
	inline Matrix4x4<T>& Matrix4x4<T>::operator=(Matrix4x4&& Right) noexcept
	{
		if (this != &Right)
		{
			M11 = Elysium::Core::Template::Move(Right.M11);
			M12 = Elysium::Core::Template::Move(Right.M12);
			M13 = Elysium::Core::Template::Move(Right.M13);
			M14 = Elysium::Core::Template::Move(Right.M14);
			M21 = Elysium::Core::Template::Move(Right.M21);
			M22 = Elysium::Core::Template::Move(Right.M22);
			M23 = Elysium::Core::Template::Move(Right.M23);
			M24 = Elysium::Core::Template::Move(Right.M24);
			M31 = Elysium::Core::Template::Move(Right.M31);
			M32 = Elysium::Core::Template::Move(Right.M32);
			M33 = Elysium::Core::Template::Move(Right.M33);
			M34 = Elysium::Core::Template::Move(Right.M34);
			M41 = Elysium::Core::Template::Move(Right.M41);
			M42 = Elysium::Core::Template::Move(Right.M42);
			M43 = Elysium::Core::Template::Move(Right.M43);
			M44 = Elysium::Core::Template::Move(Right.M44);
		}
		return *this;
	}
}
#endif
