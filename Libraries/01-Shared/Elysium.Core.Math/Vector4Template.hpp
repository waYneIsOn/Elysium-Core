/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR4TEMPLATE
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR4TEMPLATE

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _INC_MATH
#include <math.h>
#endif

#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#include "MathHelper.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	template <typename T>
	class Vector4Template
	{
	public:
		// constructors & destructor
		Vector4Template();
		Vector4Template(T Value);
		Vector4Template(T ValueX, T ValueY, T ValueZ, T ValueW);
		virtual ~Vector4Template();

		// fields
		T X;
		T Y;
		T Z;
		T W;

		// methods
		T GetLength();
		T GetLengthSquared();
		void Normalize();

		// static methods
		static void Add(Vector4Template* Value1, Vector4Template* Value2, Vector4Template& Result);
		static void Barycentric(Vector4Template* Value1, Vector4Template* Value2, Vector4Template* Value3, T Amount1, T Amount2, Vector4Template& Result);
		static void CatmullRom(Vector4Template* Value1, Vector4Template* Value2, Vector4Template* Value3, Vector4Template* Value4, T Amount, Vector4Template& Result);
		static void Clamp(Vector4Template* Value, Vector4Template* Min, Vector4Template* Max, Vector4Template& Result);
		static void Distance(Vector4Template* Value1, Vector4Template* Value2, T& Result);
		static void DistanceSquared(Vector4Template* Value1, Vector4Template* Value2, T& Result);
		static void Divide(Vector4Template* Value, T Divisor, Vector4Template& Result);
		static void Divide(Vector4Template* Value1, Vector4Template* Value2, Vector4Template& Result);
		static void Dot(Vector4Template* Value1, Vector4Template* Value2, T& Result);
		static void Hermite(Vector4Template* Value1, Vector4Template* Tangent1, Vector4Template* Value2, Vector4Template* Tangent2, T Amount, Vector4Template& Result);
		static void Lerp(Vector4Template* Value1, Vector4Template* Value2, T Amount, Vector4Template& Result);
		static void Max(Vector4Template* Value1, Vector4Template* Value2, Vector4Template& Result);
		static void Min(Vector4Template* Value1, Vector4Template* Value2, Vector4Template& Result);
		static void Multiply(Vector4Template* Value, T Multiplier, Vector4Template& Result);
		static void Multiply(Vector4Template* Value1, Vector4Template* Value2, Vector4Template& Result);
		static void Negate(Vector4Template* Value, Vector4Template& Result);
		static void Reflect(Vector4Template* Value, Vector4Template* Normal, Vector4Template& Result);
		static void SmoothStep(Vector4Template* Value1, Vector4Template* Value2, T Amount, Vector4Template& Result);
		static void Subtract(Vector4Template* Value1, Vector4Template* Value2, Vector4Template& Result);
		//static void Transform(Vector4Template* Position, Matrix* Matrix, Vector4Template& Result);
		//static void TransformNormal(Vector4Template* Normal, Matrix* Matrix, Vector4Template* Result);
	};

	template<class T>
	inline Vector4Template<T>::Vector4Template()
		: X(0), Y(0), Z(0), W(0)
	{
	}
	template<class T>
	inline Vector4Template<T>::Vector4Template(T Value)
		: X(Value), Y(Value), Z(Value), W(Value)
	{
	}
	template<class T>
	inline Vector4Template<T>::Vector4Template(T ValueX, T ValueY, T ValueZ, T ValueW)
		: X(ValueX), Y(ValueY), Z(ValueZ), W(ValueW)
	{
	}
	template<class T>
	inline Vector4Template<T>::~Vector4Template()
	{
	}

	template<class T>
	inline T Vector4Template<T>::GetLength()
	{
		return (T)sqrt(X * X + Y * Y + Z * Z + W * W);
	}
	template<class T>
	inline T Vector4Template<T>::GetLengthSquared()
	{
		return X * X + Y * Y + Z * Z + W * W;
	}
	template<class T>
	inline void Vector4Template<T>::Normalize()
	{
		T Factor = 1.0f / GetLength();
		X *= Factor;
		Y *= Factor;
		Z *= Factor;
		W *= Factor;
	}

	template<class T>
	inline void Vector4Template<T>::Add(Vector4Template * Value1, Vector4Template * Value2, Vector4Template & Result)
	{
		Result.X = Value1->X + Value2->X;
		Result.Y = Value1->Y + Value2->Y;
		Result.Z = Value1->Z + Value2->Z;
		Result.W = Value1->W + Value2->W;
	}
	template<class T>
	inline void Vector4Template<T>::Barycentric(Vector4Template * Value1, Vector4Template * Value2, Vector4Template * Value3, T Amount1, T Amount2, Vector4Template & Result)
	{
		Result.X = MathHelper::Barycentric(Value1->X, Value2->X, Value3->X, Amount1, Amount2);
		Result.Y = MathHelper::Barycentric(Value1->Y, Value2->Y, Value3->Y, Amount1, Amount2);
		Result.Z = MathHelper::Barycentric(Value1->Z, Value2->Z, Value3->Z, Amount1, Amount2);
		Result.W = MathHelper::Barycentric(Value1->W, Value2->W, Value3->W, Amount1, Amount2);
	}
	template<class T>
	inline void Vector4Template<T>::CatmullRom(Vector4Template * Value1, Vector4Template * Value2, Vector4Template * Value3, Vector4Template * Value4, T Amount, Vector4Template & Result)
	{
		// using double to not lose precission
		double AmountSquared = Amount * Amount;
		double AmountCubed = AmountSquared * Amount;

		Result.X = MathHelper::CatmullRom(Value1->X, Value2->X, Value3->X, Value4->X, Amount, AmountSquared, AmountCubed);
		Result.Y = MathHelper::CatmullRom(Value1->Y, Value2->Y, Value3->Y, Value4->Y, Amount, AmountSquared, AmountCubed);
		Result.Z = MathHelper::CatmullRom(Value1->Z, Value2->Z, Value3->Z, Value4->Z, Amount, AmountSquared, AmountCubed);
		Result.W = MathHelper::CatmullRom(Value1->W, Value2->W, Value3->W, Value4->W, Amount, AmountSquared, AmountCubed);
	}
	template<class T>
	inline void Vector4Template<T>::Clamp(Vector4Template * Value, Vector4Template * Min, Vector4Template * Max, Vector4Template & Result)
	{
		Result.X = MathHelper::Clamp(Value->X, Min->X, Max->X);
		Result.Y = MathHelper::Clamp(Value->Y, Min->Y, Max->Y);
		Result.Z = MathHelper::Clamp(Value->Z, Min->Z, Max->Z);
		Result.W = MathHelper::Clamp(Value->W, Min->W, Max->W);
	}
	template<class T>
	inline void Vector4Template<T>::Distance(Vector4Template * Value1, Vector4Template * Value2, T & Result)
	{
		Vector4Template<T> TemporaryVector;
		Subtract(Value1, Value2, TemporaryVector);
		Result = TemporaryVector.GetLength();
	}
	template<class T>
	inline void Vector4Template<T>::DistanceSquared(Vector4Template * Value1, Vector4Template * Value2, T & Result)
	{
		Vector4Template<T> TemporaryVector;
		Subtract(Value1, Value2, TemporaryVector);
		Result = TemporaryVector.GetLengthSquared();
	}
	template<class T>
	inline void Vector4Template<T>::Divide(Vector4Template * Value, T Divisor, Vector4Template & Result)
	{
		Divisor = 1.0f / Divisor;
		Result.X = Value->X * Divisor;
		Result.Y = Value->Y * Divisor;
		Result.Z = Value->Z * Divisor;
		Result.W = Value->W * Divisor;
	}
	template<class T>
	inline void Vector4Template<T>::Divide(Vector4Template * Value1, Vector4Template * Value2, Vector4Template & Result)
	{
		Result.X = Value1->X / Value2->X;
		Result.Y = Value1->Y / Value2->Y;
		Result.Z = Value1->Z / Value2->Z;
		Result.W = Value1->W / Value2->W;
	}
	template<class T>
	inline void Vector4Template<T>::Dot(Vector4Template * Value1, Vector4Template * Value2, T & Result)
	{
		Result = Value1->X * Value2->X + Value1->Y * Value2->Y + Value1->Z * Value2->Z + Value1->W * Value2->W;
	}
	template<class T>
	inline void Vector4Template<T>::Hermite(Vector4Template * Value1, Vector4Template * Tangent1, Vector4Template * Value2, Vector4Template * Tangent2, T Amount, Vector4Template & Result)
	{
		T AmountSquared = Amount * Amount;
		T AmountCubed = AmountSquared * Amount;
		T AmountCubedTimesThree = AmountSquared + AmountSquared + AmountSquared;

		Result.X = MathHelper::Hermite(Value1->X, Tangent1->X, Value2->X, Tangent2->X, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
		Result.Y = MathHelper::Hermite(Value1->Y, Tangent1->Y, Value2->Y, Tangent2->Y, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
		Result.Z = MathHelper::Hermite(Value1->Z, Tangent1->Z, Value2->Z, Tangent2->Z, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
		Result.W = MathHelper::Hermite(Value1->W, Tangent1->W, Value2->W, Tangent2->W, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
	}
	template<class T>
	inline void Vector4Template<T>::Lerp(Vector4Template * Value1, Vector4Template * Value2, T Amount, Vector4Template & Result)
	{
		Result.X = MathHelper::Lerp(Value1->X, Value2->X, Amount);
		Result.Y = MathHelper::Lerp(Value1->Y, Value2->Y, Amount);
		Result.Z = MathHelper::Lerp(Value1->Z, Value2->Z, Amount);
		Result.W = MathHelper::Lerp(Value1->W, Value2->W, Amount);
	}
	template<class T>
	inline void Vector4Template<T>::Max(Vector4Template * Value1, Vector4Template * Value2, Vector4Template & Result)
	{
		Result.X = MathHelper::Max(Value1->X, Value2->X);
		Result.Y = MathHelper::Max(Value1->Y, Value2->Y);
		Result.Z = MathHelper::Max(Value1->Z, Value2->Z);
		Result.W = MathHelper::Max(Value1->W, Value2->W);
	}
	template<class T>
	inline void Vector4Template<T>::Min(Vector4Template * Value1, Vector4Template * Value2, Vector4Template & Result)
	{
		Result.X = MathHelper::Min(Value1->X, Value2->X);
		Result.Y = MathHelper::Min(Value1->Y, Value2->Y);
		Result.Z = MathHelper::Min(Value1->Z, Value2->Z);
		Result.W = MathHelper::Min(Value1->W, Value2->W);
	}
	template<class T>
	inline void Vector4Template<T>::Multiply(Vector4Template * Value, T Multiplier, Vector4Template & Result)
	{
		Result.X = Value->X * Multiplier;
		Result.Y = Value->Y * Multiplier;
		Result.Z = Value->Z * Multiplier;
		Result.W = Value->W * Multiplier;
	}
	template<class T>
	inline void Vector4Template<T>::Multiply(Vector4Template * Value1, Vector4Template * Value2, Vector4Template & Result)
	{
		Result.X = Value1->X * Value2->X;
		Result.Y = Value1->Y * Value2->Y;
		Result.Z = Value1->Z * Value2->Z;
		Result.W = Value1->W * Value2->W;
	}
	template<class T>
	inline void Vector4Template<T>::Negate(Vector4Template * Value, Vector4Template & Result)
	{
		Result.X = -Value->X;
		Result.Y = -Value->Y;
		Result.Z = -Value->Z;
		Result.W = -Value->W;
	}
	template<class T>
	inline void Vector4Template<T>::Reflect(Vector4Template * Value, Vector4Template * Normal, Vector4Template & Result)
	{
		T Factor = 1.0f;
		Dot(Value, Normal, Factor);
		Factor *= 2;

		Result.X = Value->X - (Factor * Normal->X);
		Result.Y = Value->Y - (Factor * Normal->Y);
		Result.Z = Value->Z - (Factor * Normal->Z);
		Result.W = Value->W - (Factor * Normal->W);
	}
	template<class T>
	inline void Vector4Template<T>::SmoothStep(Vector4Template * Value1, Vector4Template * Value2, T Amount, Vector4Template & Result)
	{
		Result.X = MathHelper::SmoothStep(Value1->X, Value2->X, Amount);
		Result.Y = MathHelper::SmoothStep(Value1->Y, Value2->Y, Amount);
		Result.Z = MathHelper::SmoothStep(Value1->Z, Value2->Z, Amount);
		Result.W = MathHelper::SmoothStep(Value1->W, Value2->W, Amount);
	}
	template<class T>
	inline void Vector4Template<T>::Subtract(Vector4Template * Value1, Vector4Template * Value2, Vector4Template & Result)
	{
		Result.X = Value1->X - Value2->X;
		Result.Y = Value1->Y - Value2->Y;
		Result.Z = Value1->Z - Value2->Z;
		Result.W = Value1->W - Value2->W;
	}
}
#endif
