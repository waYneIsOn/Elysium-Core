/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_NUMERICS_MATRIX3X3TEMPLATE
#define ELYSIUM_CORE_MATH_NUMERICS_MATRIX3X3TEMPLATE

#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#include "MathHelper.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Math
		{
			namespace Numerics
			{
				template <typename T>
				class Matrix3x3Template
				{
				public:
					// constructors & destructor
					Matrix3x3Template(
						T ValueM11, T ValueM12, T ValueM13,
						T ValueM21, T ValueM22, T ValueM23,
						T ValueM31, T ValueM32, T ValueM33);
					virtual ~Matrix3x3Template();

					// fields
					T M11;
					T M12;
					T M13;

					T M21;
					T M22;
					T M23;

					T M31;
					T M32;
					T M33;

					// methods
					//bool Decompose(Vector3Template<T>& Scale, QuaternionTemplate<T>& Rotation, Vector3Template<T>& Translation);
					//T Determinant();

					// static methods
					//static void Add();
				};

				template<class T>
				inline Matrix3x3Template<T>::Matrix3x3Template(
					T ValueM11, T ValueM12, T ValueM13,
					T ValueM21, T ValueM22, T ValueM23,
					T ValueM31, T ValueM32, T ValueM33)
					: M11(ValueM11), M12(ValueM12), M13(ValueM13),
					M21(ValueM21), M22(ValueM22), M23(ValueM23),
					M31(ValueM31), M32(ValueM32), M33(ValueM33)
				{
				}
				template<class T>
				inline Matrix3x3Template<T>::~Matrix3x3Template()
				{
				}
			}
		}
	}
}
#endif
