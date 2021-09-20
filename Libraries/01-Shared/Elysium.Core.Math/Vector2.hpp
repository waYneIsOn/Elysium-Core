/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR2
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR2

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _INC_MATH
#include <math.h>
#endif

#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#include "MathHelper.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	template <class T>
	class Vector2 final
	{
	public:
		Vector2();
		Vector2(T Value);
		Vector2(T ValueX, T ValueY);
		Vector2(const Vector2& Source);
		Vector2(Vector2&& Right) noexcept;
		~Vector2();

		Vector2<T>& operator=(const Vector2& Source);
		Vector2<T>& operator=(Vector2&& Right) noexcept;

		static Vector2<T> Zero();
		static Vector2<T> One();

		static Vector2<T> UnitX();
		static Vector2<T> UnitY();
		
		T X;
		T Y;

		T GetLength();
		T GetLengthSquared();
		void Normalize();
		/*
		static void Add(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>& Result);
		static void Barycentric(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>* Value3, T Amount1, T Amount2, Vector2<T>& Result);
		static void CatmullRom(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>* Value3, Vector2<T>* Value4, T Amount, Vector2<T>& Result);
		static void Clamp(Vector2<T>* Value, Vector2<T>* Min, Vector2<T>* Max, Vector2<T>& Result);
		static void Distance(Vector2<T>* Value1, Vector2<T>* Value2, T& Result);
		static void DistanceSquared(Vector2<T>* Value1, Vector2<T>* Value2, T& Result);
		static void Divide(Vector2<T>* Value, T Divisor, Vector2<T>& Result);
		static void Divide(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>& Result);
		static void Dot(Vector2<T>* Value1, Vector2<T>* Value2, T& Result);
		static void Hermite(Vector2<T>* Value1, Vector2<T>* Tangent1, Vector2<T>* Value2, Vector2<T>* Tangent2, T Amount, Vector2<T>& Result);
		static void Lerp(Vector2<T>* Value1, Vector2<T>* Value2, T Amount, Vector2<T>& Result);
		static void Max(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>& Result);
		static void Min(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>& Result);
		static void Multiply(Vector2<T>* Value, T Multiplier, Vector2<T>& Result);
		static void Multiply(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>& Result);
		static void Negate(Vector2<T>* Value, Vector2<T>& Result);
		static void Reflect(Vector2<T>* Value, Vector2<T>* Normal, Vector2<T>& Result);
		static void SmoothStep(Vector2<T>* Value1, Vector2<T>* Value2, T Amount, Vector2<T>& Result);
		static void Subtract(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>& Result);
		//static void Transform(Vector2<T>* Position, Matrix* Matrix, Vector2<T>& Result);
		//static void TransformNormal(Vector2<T>* Normal, Matrix* Matrix, Vector2<T>* Result);
		*/
	};

	template<class T>
	inline Vector2<T>::Vector2()
		: X(0), Y(0)
	{ }
	template<class T>
	inline Vector2<T>::Vector2(T Value)
		: X(Value), Y(Value)
	{ }
	template<class T>
	inline Vector2<T>::Vector2(T ValueX, T ValueY)
		: X(ValueX), Y(ValueY)
	{ }
	template<class T>
	inline Vector2<T>::Vector2(const Vector2 & Source)
		: X(Source.X), Y(Source.Y)
	{ }
	template<class T>
	inline Vector2<T>::Vector2(Vector2&& Right) noexcept
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}
	template<class T>
	inline Vector2<T>::~Vector2()
	{ }

	template<class T>
	inline Vector2<T>& Vector2<T>::operator=(const Vector2 & Source)
	{
		if (this != &Source)
		{
			X = Source.X;
			Y = Source.Y;
		}
		return *this;
	}

	template<class T>
	inline Vector2<T>& Vector2<T>::operator=(Vector2&& Right) noexcept
	{
		if (this != &Right)
		{
			X = Elysium::Core::Template::Functional::Move(Right.X);
			Y = Elysium::Core::Template::Functional::Move(Right.Y);
		}
		return *this;
	}

	template<class T>
	inline Vector2<T> Vector2<T>::Zero()
	{
		return Vector2<T>(static_cast<T>(0));
	}

	template<class T>
	inline Vector2<T> Vector2<T>::One()
	{
		return Vector2<T>(static_cast<T>(1));
	}

	template<class T>
	inline Vector2<T> Vector2<T>::UnitX()
	{
		return Vector2<T>(static_cast<T>(1), static_cast<T>(0));
	}

	template<class T>
	inline Vector2<T> Vector2<T>::UnitY()
	{
		return Vector2<T>(static_cast<T>(0), static_cast<T>(1));
	}

	template<class T>
	inline T Vector2<T>::GetLength()
	{
		return (T)sqrt(X * X + Y * Y);
	}
	template<class T>
	inline T Vector2<T>::GetLengthSquared()
	{
		return X * X + Y * Y;
	}
	template<class T>
	inline void Vector2<T>::Normalize()
	{
		T Factor = (T)1.0 / GetLength();
		X *= Factor;
		Y *= Factor;
	}
	/*
	template<class T>
	inline void Vector2<T>::Add(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>& Result)
	{
		Result.X = Value1->X + Value2->X;
		Result.Y = Value1->Y + Value2->Y;
	}
	template<class T>
	inline void Vector2<T>::Barycentric(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>* Value3, T Amount1, T Amount2, Vector2<T>& Result)
	{
		Result.X = MathHelper::Barycentric(Value1->X, Value2->X, Value3->X, Amount1, Amount2);
		Result.Y = MathHelper::Barycentric(Value1->Y, Value2->Y, Value3->Y, Amount1, Amount2);
	}
	template<class T>
	inline void Vector2<T>::CatmullRom(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>* Value3, Vector2<T>* Value4, T Amount, Vector2<T>& Result)
	{
		// using double to not lose precission
		double AmountSquared = Amount * Amount;
		double AmountCubed = AmountSquared * Amount;

		Result.X = MathHelper::CatmullRom(Value1->X, Value2->X, Value3->X, Value4->X, Amount, AmountSquared, AmountCubed);
		Result.Y = MathHelper::CatmullRom(Value1->Y, Value2->Y, Value3->Y, Value4->Y, Amount, AmountSquared, AmountCubed);
	}
	template<class T>
	inline void Vector2<T>::Clamp(Vector2<T>* Value, Vector2<T>* Min, Vector2<T>* Max, Vector2<T>& Result)
	{
		Result.X = MathHelper::Clamp(Value->X, Min->X, Max->X);
		Result.Y = MathHelper::Clamp(Value->Y, Min->Y, Max->Y);
	}
	template<class T>
	inline void Vector2<T>::Distance(Vector2<T>* Value1, Vector2<T>* Value2, T & Result)
	{
		Vector2<T> TemporaryVector;
		Subtract(Value1, Value2, TemporaryVector);
		Result = TemporaryVector.GetLength();
	}
	template<class T>
	inline void Vector2<T>::DistanceSquared(Vector2<T>* Value1, Vector2<T>* Value2, T & Result)
	{
		Vector2<T> TemporaryVector;
		Subtract(Value1, Value2, TemporaryVector);
		Result = TemporaryVector.GetLengthSquared();
	}
	template<class T>
	inline void Vector2<T>::Divide(Vector2<T>* Value, T Divisor, Vector2<T>& Result)
	{
		Divisor = 1.0f / Divisor;
		Result.X = Value->X * Divisor;
		Result.Y = Value->Y * Divisor;
	}
	template<class T>
	inline void Vector2<T>::Divide(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>& Result)
	{
		Result.X = Value1->X / Value2->X;
		Result.Y = Value1->Y / Value2->Y;
	}
	template<class T>
	inline void Vector2<T>::Dot(Vector2<T>* Value1, Vector2<T>* Value2, T & Result)
	{
		Result = Value1->X * Value2->X + Value1->Y * Value2->Y;
	}
	template<class T>
	inline void Vector2<T>::Hermite(Vector2<T>* Value1, Vector2<T>* Tangent1, Vector2<T>* Value2, Vector2<T>* Tangent2, T Amount, Vector2<T>& Result)
	{
		T AmountSquared = Amount * Amount;
		T AmountCubed = AmountSquared * Amount;
		T AmountCubedTimesThree = AmountSquared + AmountSquared + AmountSquared;

		Result.X = MathHelper::Hermite(Value1->X, Tangent1->X, Value2->X, Tangent2->X, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
		Result.Y = MathHelper::Hermite(Value1->Y, Tangent1->Y, Value2->Y, Tangent2->Y, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
	}
	template<class T>
	inline void Vector2<T>::Lerp(Vector2<T>* Value1, Vector2<T>* Value2, T Amount, Vector2<T>& Result)
	{
		Result.X = MathHelper::Lerp(Value1->X, Value2->X, Amount);
		Result.Y = MathHelper::Lerp(Value1->Y, Value2->Y, Amount);
	}
	template<class T>
	inline void Vector2<T>::Max(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>& Result)
	{
		Result.X = MathHelper::Max(Value1->X, Value2->X);
		Result.Y = MathHelper::Max(Value1->Y, Value2->Y);
	}
	template<class T>
	inline void Vector2<T>::Min(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>& Result)
	{
		Result.X = MathHelper::Min(Value1->X, Value2->X);
		Result.Y = MathHelper::Min(Value1->Y, Value2->Y);
	}
	template<class T>
	inline void Vector2<T>::Multiply(Vector2<T>* Value, T Multiplier, Vector2<T>& Result)
	{
		Result.X = Value->X * Multiplier;
		Result.Y = Value->Y * Multiplier;
	}
	template<class T>
	inline void Vector2<T>::Multiply(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>& Result)
	{
		Result.X = Value1->X * Value2->X;
		Result.Y = Value1->Y * Value2->Y;
	}
	template<class T>
	inline void Vector2<T>::Negate(Vector2<T>* Value, Vector2<T>& Result)
	{
		Result.X = -Value->X;
		Result.Y = -Value->Y;
	}
	template<class T>
	inline void Vector2<T>::Reflect(Vector2<T>* Value, Vector2<T>* Normal, Vector2<T>& Result)
	{
		T Factor = 1.0f;
		Dot(Value, Normal, Factor);
		Factor *= 2;

		Result.X = Value->X - (Factor * Normal->X);
		Result.Y = Value->Y - (Factor * Normal->Y);
	}
	template<class T>
	inline void Vector2<T>::SmoothStep(Vector2<T>* Value1, Vector2<T>* Value2, T Amount, Vector2<T>& Result)
	{
		Result.X = MathHelper::SmoothStep(Value1->X, Value2->X, Amount);
		Result.Y = MathHelper::SmoothStep(Value1->Y, Value2->Y, Amount);
	}
	template<class T>
	inline void Vector2<T>::Subtract(Vector2<T>* Value1, Vector2<T>* Value2, Vector2<T>& Result)
	{
		Result.X = Value1->X - Value2->X;
		Result.Y = Value1->Y - Value2->Y;
	}
	*/
}
#endif
