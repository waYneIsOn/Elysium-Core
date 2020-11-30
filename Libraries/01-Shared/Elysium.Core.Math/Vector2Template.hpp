/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2TEMPLATE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR2TEMPLATE

#ifdef _MSC_VER
#pragma once
#endif

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
				class Vector2Template
				{
				public:
					// constructors & destructor
					Vector2Template();
					Vector2Template(T Value);
					Vector2Template(T ValueX, T ValueY);
					virtual ~Vector2Template();

					// fields
					T X;
					T Y;

					// methods
					T GetLength();
					T GetLengthSquared();
					void Normalize();

					// static methods
					static void Add(Vector2Template* Value1, Vector2Template* Value2, Vector2Template& Result);
					static void Barycentric(Vector2Template* Value1, Vector2Template* Value2, Vector2Template* Value3, T Amount1, T Amount2, Vector2Template& Result);
					static void CatmullRom(Vector2Template* Value1, Vector2Template* Value2, Vector2Template* Value3, Vector2Template* Value4, T Amount, Vector2Template& Result);
					static void Clamp(Vector2Template* Value, Vector2Template* Min, Vector2Template* Max, Vector2Template& Result);
					static void Distance(Vector2Template* Value1, Vector2Template* Value2, T& Result);
					static void DistanceSquared(Vector2Template* Value1, Vector2Template* Value2, T& Result);
					static void Divide(Vector2Template* Value, T Divisor, Vector2Template& Result);
					static void Divide(Vector2Template* Value1, Vector2Template* Value2, Vector2Template& Result);
					static void Dot(Vector2Template* Value1, Vector2Template* Value2, T& Result);
					static void Hermite(Vector2Template* Value1, Vector2Template* Tangent1, Vector2Template* Value2, Vector2Template* Tangent2, T Amount, Vector2Template& Result);
					static void Lerp(Vector2Template* Value1, Vector2Template* Value2, T Amount, Vector2Template& Result);
					static void Max(Vector2Template* Value1, Vector2Template* Value2, Vector2Template& Result);
					static void Min(Vector2Template* Value1, Vector2Template* Value2, Vector2Template& Result);
					static void Multiply(Vector2Template* Value, T Multiplier, Vector2Template& Result);
					static void Multiply(Vector2Template* Value1, Vector2Template* Value2, Vector2Template& Result);
					static void Negate(Vector2Template* Value, Vector2Template& Result);
					static void Reflect(Vector2Template* Value, Vector2Template* Normal, Vector2Template& Result);
					static void SmoothStep(Vector2Template* Value1, Vector2Template* Value2, T Amount, Vector2Template& Result);
					static void Subtract(Vector2Template* Value1, Vector2Template* Value2, Vector2Template& Result);
					//static void Transform(Vector2Template* Position, Matrix* Matrix, Vector2Template& Result);
					//static void TransformNormal(Vector2Template* Normal, Matrix* Matrix, Vector2Template* Result);
				};

				template<class T>
				inline Vector2Template<T>::Vector2Template()
					: X(0), Y(0)
				{
				}
				template<class T>
				inline Vector2Template<T>::Vector2Template(T Value)
					: X(Value), Y(Value)
				{
				}
				template<class T>
				inline Vector2Template<T>::Vector2Template(T ValueX, T ValueY)
					: X(ValueX), Y(ValueY)
				{
				}
				template<class T>
				inline Vector2Template<T>::~Vector2Template()
				{
				}

				template<class T>
				inline T Vector2Template<T>::GetLength()
				{
					return (T)sqrt(X * X + Y * Y);
				}
				template<class T>
				inline T Vector2Template<T>::GetLengthSquared()
				{
					return X * X + Y * Y;
				}
				template<class T>
				inline void Vector2Template<T>::Normalize()
				{
					T Factor = (T)1.0 / GetLength();
					X *= Factor;
					Y *= Factor;
				}

				template<class T>
				inline void Vector2Template<T>::Add(Vector2Template * Value1, Vector2Template * Value2, Vector2Template & Result)
				{
					Result.X = Value1->X + Value2->X;
					Result.Y = Value1->Y + Value2->Y;
				}
				template<class T>
				inline void Vector2Template<T>::Barycentric(Vector2Template * Value1, Vector2Template * Value2, Vector2Template * Value3, T Amount1, T Amount2, Vector2Template & Result)
				{
					Result.X = MathHelper::Barycentric(Value1->X, Value2->X, Value3->X, Amount1, Amount2);
					Result.Y = MathHelper::Barycentric(Value1->Y, Value2->Y, Value3->Y, Amount1, Amount2);
				}
				template<class T>
				inline void Vector2Template<T>::CatmullRom(Vector2Template * Value1, Vector2Template * Value2, Vector2Template * Value3, Vector2Template * Value4, T Amount, Vector2Template & Result)
				{
					// using double to not lose precission
					double AmountSquared = Amount * Amount;
					double AmountCubed = AmountSquared * Amount;

					Result.X = MathHelper::CatmullRom(Value1->X, Value2->X, Value3->X, Value4->X, Amount, AmountSquared, AmountCubed);
					Result.Y = MathHelper::CatmullRom(Value1->Y, Value2->Y, Value3->Y, Value4->Y, Amount, AmountSquared, AmountCubed);
				}
				template<class T>
				inline void Vector2Template<T>::Clamp(Vector2Template * Value, Vector2Template * Min, Vector2Template * Max, Vector2Template & Result)
				{
					Result.X = MathHelper::Clamp(Value->X, Min->X, Max->X);
					Result.Y = MathHelper::Clamp(Value->Y, Min->Y, Max->Y);
				}
				template<class T>
				inline void Vector2Template<T>::Distance(Vector2Template * Value1, Vector2Template * Value2, T & Result)
				{
					Vector2Template<T> TemporaryVector;
					Subtract(Value1, Value2, TemporaryVector);
					Result = TemporaryVector.GetLength();
				}
				template<class T>
				inline void Vector2Template<T>::DistanceSquared(Vector2Template * Value1, Vector2Template * Value2, T & Result)
				{
					Vector2Template<T> TemporaryVector;
					Subtract(Value1, Value2, TemporaryVector);
					Result = TemporaryVector.GetLengthSquared();
				}
				template<class T>
				inline void Vector2Template<T>::Divide(Vector2Template * Value, T Divisor, Vector2Template & Result)
				{
					Divisor = 1.0f / Divisor;
					Result.X = Value->X * Divisor;
					Result.Y = Value->Y * Divisor;
				}
				template<class T>
				inline void Vector2Template<T>::Divide(Vector2Template * Value1, Vector2Template * Value2, Vector2Template & Result)
				{
					Result.X = Value1->X / Value2->X;
					Result.Y = Value1->Y / Value2->Y;
				}
				template<class T>
				inline void Vector2Template<T>::Dot(Vector2Template * Value1, Vector2Template * Value2, T & Result)
				{
					Result = Value1->X * Value2->X + Value1->Y * Value2->Y;
				}
				template<class T>
				inline void Vector2Template<T>::Hermite(Vector2Template * Value1, Vector2Template * Tangent1, Vector2Template * Value2, Vector2Template * Tangent2, T Amount, Vector2Template & Result)
				{
					T AmountSquared = Amount * Amount;
					T AmountCubed = AmountSquared * Amount;
					T AmountCubedTimesThree = AmountSquared + AmountSquared + AmountSquared;

					Result.X = MathHelper::Hermite(Value1->X, Tangent1->X, Value2->X, Tangent2->X, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
					Result.Y = MathHelper::Hermite(Value1->Y, Tangent1->Y, Value2->Y, Tangent2->Y, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
				}
				template<class T>
				inline void Vector2Template<T>::Lerp(Vector2Template * Value1, Vector2Template * Value2, T Amount, Vector2Template & Result)
				{
					Result.X = MathHelper::Lerp(Value1->X, Value2->X, Amount);
					Result.Y = MathHelper::Lerp(Value1->Y, Value2->Y, Amount);
				}
				template<class T>
				inline void Vector2Template<T>::Max(Vector2Template * Value1, Vector2Template * Value2, Vector2Template & Result)
				{
					Result.X = MathHelper::Max(Value1->X, Value2->X);
					Result.Y = MathHelper::Max(Value1->Y, Value2->Y);
				}
				template<class T>
				inline void Vector2Template<T>::Min(Vector2Template * Value1, Vector2Template * Value2, Vector2Template & Result)
				{
					Result.X = MathHelper::Min(Value1->X, Value2->X);
					Result.Y = MathHelper::Min(Value1->Y, Value2->Y);
				}
				template<class T>
				inline void Vector2Template<T>::Multiply(Vector2Template * Value, T Multiplier, Vector2Template & Result)
				{
					Result.X = Value->X * Multiplier;
					Result.Y = Value->Y * Multiplier;
				}
				template<class T>
				inline void Vector2Template<T>::Multiply(Vector2Template * Value1, Vector2Template * Value2, Vector2Template & Result)
				{
					Result.X = Value1->X * Value2->X;
					Result.Y = Value1->Y * Value2->Y;
				}
				template<class T>
				inline void Vector2Template<T>::Negate(Vector2Template * Value, Vector2Template & Result)
				{
					Result.X = -Value->X;
					Result.Y = -Value->Y;
				}
				template<class T>
				inline void Vector2Template<T>::Reflect(Vector2Template * Value, Vector2Template * Normal, Vector2Template & Result)
				{
					T Factor = 1.0f;
					Dot(Value, Normal, Factor);
					Factor *= 2;

					Result.X = Value->X - (Factor * Normal->X);
					Result.Y = Value->Y - (Factor * Normal->Y);
				}
				template<class T>
				inline void Vector2Template<T>::SmoothStep(Vector2Template * Value1, Vector2Template * Value2, T Amount, Vector2Template & Result)
				{
					Result.X = MathHelper::SmoothStep(Value1->X, Value2->X, Amount);
					Result.Y = MathHelper::SmoothStep(Value1->Y, Value2->Y, Amount);
				}
				template<class T>
				inline void Vector2Template<T>::Subtract(Vector2Template * Value1, Vector2Template * Value2, Vector2Template & Result)
				{
					Result.X = Value1->X - Value2->X;
					Result.Y = Value1->Y - Value2->Y;
				}
			}
		}
	}
}
#endif
