/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3TEMPLATE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR3TEMPLATE

#ifndef _INC_MATH
#include <math.h>
#endif

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
				template <class T>
				class Vector3Template
				{
				public:
					// constructors & destructor
					Vector3Template();
					Vector3Template(T Value);
					Vector3Template(T ValueX, T ValueY, T ValueZ);
					virtual ~Vector3Template();

					// fields
					T X;
					T Y;
					T Z;

					// methods
					T GetLength();
					T GetLengthSquared();
					void Normalize();

					// static methods
					static void Add(Vector3Template* Value1, Vector3Template* Value2, Vector3Template& Result);
					static void Barycentric(Vector3Template* Value1, Vector3Template* Value2, Vector3Template* Value3, T Amount1, T Amount2, Vector3Template& Result);
					static void CatmullRom(Vector3Template* Value1, Vector3Template* Value2, Vector3Template* Value3, Vector3Template* Value4, T Amount, Vector3Template& Result);
					static void Clamp(Vector3Template* Value, Vector3Template* Min, Vector3Template* Max, Vector3Template& Result);
					static void Distance(Vector3Template* Value1, Vector3Template* Value2, T& Result);
					static void DistanceSquared(Vector3Template* Value1, Vector3Template* Value2, T& Result);
					static void Divide(Vector3Template* Value, T Divisor, Vector3Template& Result);
					static void Divide(Vector3Template* Value1, Vector3Template* Value2, Vector3Template& Result);
					static void Dot(Vector3Template* Value1, Vector3Template* Value2, T& Result);
					static void Hermite(Vector3Template* Value1, Vector3Template* Tangent1, Vector3Template* Value2, Vector3Template* Tangent2, T Amount, Vector3Template& Result);
					static void Lerp(Vector3Template* Value1, Vector3Template* Value2, T Amount, Vector3Template& Result);
					static void Max(Vector3Template* Value1, Vector3Template* Value2, Vector3Template& Result);
					static void Min(Vector3Template* Value1, Vector3Template* Value2, Vector3Template& Result);
					static void Multiply(Vector3Template* Value, T Multiplier, Vector3Template& Result);
					static void Multiply(Vector3Template* Value1, Vector3Template* Value2, Vector3Template& Result);
					static void Negate(Vector3Template* Value, Vector3Template& Result);
					static void Reflect(Vector3Template* Value, Vector3Template* Normal, Vector3Template& Result);
					static void SmoothStep(Vector3Template* Value1, Vector3Template* Value2, T Amount, Vector3Template& Result);
					static void Subtract(Vector3Template* Value1, Vector3Template* Value2, Vector3Template& Result);
					//static void Transform(Vector3Template* Position, Matrix* Matrix, Vector3Template& Result);
					//static void TransformNormal(Vector3Template* Normal, Matrix* Matrix, Vector3Template* Result);
				};

				template<class T>
				inline Vector3Template<T>::Vector3Template()
					: X(0), Y(0), Z(0)
				{
				}
				template<class T>
				inline Vector3Template<T>::Vector3Template(T Value)
					: X(Value), Y(Value), Z(Value)
				{
				}
				template<class T>
				inline Vector3Template<T>::Vector3Template(T ValueX, T ValueY, T ValueZ)
					: X(ValueX), Y(ValueY), Z(ValueZ)
				{
				}
				template<class T>
				inline Vector3Template<T>::~Vector3Template()
				{
				}

				template<class T>
				inline T Vector3Template<T>::GetLength()
				{
					return (T)sqrt(X * X + Y * Y + Z * Z);
				}
				template<class T>
				inline T Vector3Template<T>::GetLengthSquared()
				{
					return X * X + Y * Y + Z * Z;
				}
				template<class T>
				inline void Vector3Template<T>::Normalize()
				{
					T Factor = 1.0f / GetLength();
					X *= Factor;
					Y *= Factor;
					Z *= Factor;
				}

				template<class T>
				inline void Vector3Template<T>::Add(Vector3Template * Value1, Vector3Template * Value2, Vector3Template & Result)
				{
					Result.X = Value1->X + Value2->X;
					Result.Y = Value1->Y + Value2->Y;
					Result.Z = Value1->Z + Value2->Z;
				}
				template<class T>
				inline void Vector3Template<T>::Barycentric(Vector3Template * Value1, Vector3Template * Value2, Vector3Template * Value3, T Amount1, T Amount2, Vector3Template & Result)
				{
					Result.X = MathHelper::Barycentric(Value1->X, Value2->X, Value3->X, Amount1, Amount2);
					Result.Y = MathHelper::Barycentric(Value1->Y, Value2->Y, Value3->Y, Amount1, Amount2);
					Result.Z = MathHelper::Barycentric(Value1->Z, Value2->Z, Value3->Z, Amount1, Amount2);
				}
				template<class T>
				inline void Vector3Template<T>::CatmullRom(Vector3Template * Value1, Vector3Template * Value2, Vector3Template * Value3, Vector3Template * Value4, T Amount, Vector3Template & Result)
				{
					// using double to not lose precission
					double AmountSquared = Amount * Amount;
					double AmountCubed = AmountSquared * Amount;

					Result.X = MathHelper::CatmullRom(Value1->X, Value2->X, Value3->X, Value4->X, Amount, AmountSquared, AmountCubed);
					Result.Y = MathHelper::CatmullRom(Value1->Y, Value2->Y, Value3->Y, Value4->Y, Amount, AmountSquared, AmountCubed);
					Result.Z = MathHelper::CatmullRom(Value1->Z, Value2->Z, Value3->Z, Value4->Z, Amount, AmountSquared, AmountCubed);
				}
				template<class T>
				inline void Vector3Template<T>::Clamp(Vector3Template * Value, Vector3Template * Min, Vector3Template * Max, Vector3Template & Result)
				{
					Result.X = MathHelper::Clamp(Value->X, Min->X, Max->X);
					Result.Y = MathHelper::Clamp(Value->Y, Min->Y, Max->Y);
					Result.Z = MathHelper::Clamp(Value->Z, Min->Z, Max->Z);
				}
				template<class T>
				inline void Vector3Template<T>::Distance(Vector3Template * Value1, Vector3Template * Value2, T & Result)
				{
					Vector3Template<T> TemporaryVector;
					Subtract(Value1, Value2, TemporaryVector);
					Result = TemporaryVector.GetLength();
				}
				template<class T>
				inline void Vector3Template<T>::DistanceSquared(Vector3Template * Value1, Vector3Template * Value2, T & Result)
				{
					Vector3Template<T> TemporaryVector;
					Subtract(Value1, Value2, TemporaryVector);
					Result = TemporaryVector.GetLengthSquared();
				}
				template<class T>
				inline void Vector3Template<T>::Divide(Vector3Template * Value, T Divisor, Vector3Template & Result)
				{
					Divisor = 1.0f / Divisor;
					Result.X = Value->X * Divisor;
					Result.Y = Value->Y * Divisor;
					Result.Z = Value->Z * Divisor;
				}
				template<class T>
				inline void Vector3Template<T>::Divide(Vector3Template * Value1, Vector3Template * Value2, Vector3Template & Result)
				{
					Result.X = Value1->X / Value2->X;
					Result.Y = Value1->Y / Value2->Y;
					Result.Z = Value1->Z / Value2->Z;
				}
				template<class T>
				inline void Vector3Template<T>::Dot(Vector3Template * Value1, Vector3Template * Value2, T & Result)
				{
					Result = Value1->X * Value2->X + Value1->Y * Value2->Y + Value1->Z * Value2->Z;
				}
				template<class T>
				inline void Vector3Template<T>::Hermite(Vector3Template * Value1, Vector3Template * Tangent1, Vector3Template * Value2, Vector3Template * Tangent2, T Amount, Vector3Template & Result)
				{
					T AmountSquared = Amount * Amount;
					T AmountCubed = AmountSquared * Amount;
					T AmountCubedTimesThree = AmountSquared + AmountSquared + AmountSquared;

					Result.X = MathHelper::Hermite(Value1->X, Tangent1->X, Value2->X, Tangent2->X, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
					Result.Y = MathHelper::Hermite(Value1->Y, Tangent1->Y, Value2->Y, Tangent2->Y, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
					Result.Z = MathHelper::Hermite(Value1->Z, Tangent1->Z, Value2->Z, Tangent2->Z, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
				}
				template<class T>
				inline void Vector3Template<T>::Lerp(Vector3Template * Value1, Vector3Template * Value2, T Amount, Vector3Template & Result)
				{
					Result.X = MathHelper::Lerp(Value1->X, Value2->X, Amount);
					Result.Y = MathHelper::Lerp(Value1->Y, Value2->Y, Amount);
					Result.Z = MathHelper::Lerp(Value1->Z, Value2->Z, Amount);
				}
				template<class T>
				inline void Vector3Template<T>::Max(Vector3Template * Value1, Vector3Template * Value2, Vector3Template & Result)
				{
					Result.X = MathHelper::Max(Value1->X, Value2->X);
					Result.Y = MathHelper::Max(Value1->Y, Value2->Y);
					Result.Z = MathHelper::Max(Value1->Z, Value2->Z);
				}
				template<class T>
				inline void Vector3Template<T>::Min(Vector3Template * Value1, Vector3Template * Value2, Vector3Template & Result)
				{
					Result.X = MathHelper::Min(Value1->X, Value2->X);
					Result.Y = MathHelper::Min(Value1->Y, Value2->Y);
					Result.Z = MathHelper::Min(Value1->Z, Value2->Z);
				}
				template<class T>
				inline void Vector3Template<T>::Multiply(Vector3Template * Value, T Multiplier, Vector3Template & Result)
				{
					Result.X = Value->X * Multiplier;
					Result.Y = Value->Y * Multiplier;
					Result.Z = Value->Z * Multiplier;
				}
				template<class T>
				inline void Vector3Template<T>::Multiply(Vector3Template * Value1, Vector3Template * Value2, Vector3Template & Result)
				{
					Result.X = Value1->X * Value2->X;
					Result.Y = Value1->Y * Value2->Y;
					Result.Z = Value1->Z * Value2->Z;
				}
				template<class T>
				inline void Vector3Template<T>::Negate(Vector3Template * Value, Vector3Template & Result)
				{
					Result.X = -Value->X;
					Result.Y = -Value->Y;
					Result.Z = -Value->Z;
				}
				template<class T>
				inline void Vector3Template<T>::Reflect(Vector3Template * Value, Vector3Template * Normal, Vector3Template & Result)
				{
					T Factor = 1.0f;
					Dot(Value, Normal, Factor);
					Factor *= 2;

					Result.X = Value->X - (Factor * Normal->X);
					Result.Y = Value->Y - (Factor * Normal->Y);
					Result.Z = Value->Z - (Factor * Normal->Z);
				}
				template<class T>
				inline void Vector3Template<T>::SmoothStep(Vector3Template * Value1, Vector3Template * Value2, T Amount, Vector3Template & Result)
				{
					Result.X = MathHelper::SmoothStep(Value1->X, Value2->X, Amount);
					Result.Y = MathHelper::SmoothStep(Value1->Y, Value2->Y, Amount);
					Result.Z = MathHelper::SmoothStep(Value1->Z, Value2->Z, Amount);
				}
				template<class T>
				inline void Vector3Template<T>::Subtract(Vector3Template * Value1, Vector3Template * Value2, Vector3Template & Result)
				{
					Result.X = Value1->X - Value2->X;
					Result.Y = Value1->Y - Value2->Y;
					Result.Z = Value1->Z - Value2->Z;
				}
			}
		}
	}
}
#endif
