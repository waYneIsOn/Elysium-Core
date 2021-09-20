/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR4
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR4

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
	template <typename T>
	class Vector4 final
	{
	public:
		Vector4();
		Vector4(T Value);
		Vector4(T ValueX, T ValueY, T ValueZ, T ValueW);
		Vector4(const Vector4& Source);
		Vector4(Vector4&& Right) noexcept;
		~Vector4();

		Vector4<T>& operator=(const Vector4& Source);
		Vector4<T>& operator=(Vector4&& Right) noexcept;

		static Vector4<T> Zero();
		static Vector4<T> One();

		static Vector4<T> UnitX();
		static Vector4<T> UnitY();
		static Vector4<T> UnitZ();
		static Vector4<T> UnitW();

		T X;
		T Y;
		T Z;
		T W;

		T GetLength();
		T GetLengthSquared();
		void Normalize();
		/*
		static void Add(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>& Result);
		static void Barycentric(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>* Value3, T Amount1, T Amount2, Vector4<T>& Result);
		static void CatmullRom(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>* Value3, Vector4<T>* Value4, T Amount, Vector4<T>& Result);
		static void Clamp(Vector4<T>* Value, Vector4<T>* Min, Vector4<T>* Max, Vector4<T>& Result);
		static void Distance(Vector4<T>* Value1, Vector4<T>* Value2, T& Result);
		static void DistanceSquared(Vector4<T>* Value1, Vector4<T>* Value2, T& Result);
		static void Divide(Vector4<T>* Value, T Divisor, Vector4<T>& Result);
		static void Divide(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>& Result);
		static void Dot(Vector4<T>* Value1, Vector4<T>* Value2, T& Result);
		static void Hermite(Vector4<T>* Value1, Vector4<T>* Tangent1, Vector4<T>* Value2, Vector4<T>* Tangent2, T Amount, Vector4<T>& Result);
		static void Lerp(Vector4<T>* Value1, Vector4<T>* Value2, T Amount, Vector4<T>& Result);
		static void Max(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>& Result);
		static void Min(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>& Result);
		static void Multiply(Vector4<T>* Value, T Multiplier, Vector4<T>& Result);
		static void Multiply(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>& Result);
		static void Negate(Vector4<T>* Value, Vector4<T>& Result);
		static void Reflect(Vector4<T>* Value, Vector4<T>* Normal, Vector4<T>& Result);
		static void SmoothStep(Vector4<T>* Value1, Vector4<T>* Value2, T Amount, Vector4<T>& Result);
		static void Subtract(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>& Result);
		//static void Transform(Vector4<T>* Position, Matrix* Matrix, Vector4<T>& Result);
		//static void TransformNormal(Vector4<T>* Normal, Matrix* Matrix, Vector4<T>* Result);
		*/
	};

	template<class T>
	inline Vector4<T>::Vector4()
		: X(0), Y(0), Z(0), W(0)
	{ }
	template<class T>
	inline Vector4<T>::Vector4(T Value)
		: X(Value), Y(Value), Z(Value), W(Value)
	{ }
	template<class T>
	inline Vector4<T>::Vector4(T ValueX, T ValueY, T ValueZ, T ValueW)
		: X(ValueX), Y(ValueY), Z(ValueZ), W(ValueW)
	{ }
	template<typename T>
	inline Vector4<T>::Vector4(const Vector4 & Source)
		: X(Source.X), Y(Source.Y), Z(Source.Z), W(Source.W)
	{ }
	template<typename T>
	inline Vector4<T>::Vector4(Vector4&& Right) noexcept
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}
	template<class T>
	inline Vector4<T>::~Vector4()
	{ }

	template<typename T>
	inline Vector4<T>& Vector4<T>::operator=(const Vector4 & Source)
	{
		if (this != &Source)
		{
			X = Source.X;
			Y = Source.Y;
			Z = Source.Z;
			W = Source.W;
		}
		return *this;
	}

	template<typename T>
	inline Vector4<T>& Vector4<T>::operator=(Vector4&& Right) noexcept
	{
		if (this != &Right)
		{
			X = Elysium::Core::Template::Functional::Move(Right.X);
			Y = Elysium::Core::Template::Functional::Move(Right.Y);
			Z = Elysium::Core::Template::Functional::Move(Right.Z);
			W = Elysium::Core::Template::Functional::Move(Right.W);
		}
		return *this;
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::Zero()
	{
		return Vector4<T>(static_cast<T>(0));
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::One()
	{
		return Vector4<T>(static_cast<T>(1));
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::UnitX()
	{
		return Vector4<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0), static_cast<T>(0));
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::UnitY()
	{
		return Vector4<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::UnitZ()
	{
		return Vector4<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
	}

	template<typename T>
	inline Vector4<T> Vector4<T>::UnitW()
	{
		return Vector4<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
	}

	template<class T>
	inline T Vector4<T>::GetLength()
	{
		return (T)sqrt(X * X + Y * Y + Z * Z + W * W);
	}
	template<class T>
	inline T Vector4<T>::GetLengthSquared()
	{
		return X * X + Y * Y + Z * Z + W * W;
	}
	template<class T>
	inline void Vector4<T>::Normalize()
	{
		T Factor = 1.0f / GetLength();
		X *= Factor;
		Y *= Factor;
		Z *= Factor;
		W *= Factor;
	}
	/*
	template<class T>
	inline void Vector4<T>::Add(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>& Result)
	{
		Result.X = Value1->X + Value2->X;
		Result.Y = Value1->Y + Value2->Y;
		Result.Z = Value1->Z + Value2->Z;
		Result.W = Value1->W + Value2->W;
	}
	template<class T>
	inline void Vector4<T>::Barycentric(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>* Value3, T Amount1, T Amount2, Vector4<T>& Result)
	{
		Result.X = MathHelper::Barycentric(Value1->X, Value2->X, Value3->X, Amount1, Amount2);
		Result.Y = MathHelper::Barycentric(Value1->Y, Value2->Y, Value3->Y, Amount1, Amount2);
		Result.Z = MathHelper::Barycentric(Value1->Z, Value2->Z, Value3->Z, Amount1, Amount2);
		Result.W = MathHelper::Barycentric(Value1->W, Value2->W, Value3->W, Amount1, Amount2);
	}
	template<class T>
	inline void Vector4<T>::CatmullRom(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>* Value3, Vector4<T>* Value4, T Amount, Vector4<T>& Result)
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
	inline void Vector4<T>::Clamp(Vector4<T>* Value, Vector4<T>* Min, Vector4<T>* Max, Vector4<T>& Result)
	{
		Result.X = MathHelper::Clamp(Value->X, Min->X, Max->X);
		Result.Y = MathHelper::Clamp(Value->Y, Min->Y, Max->Y);
		Result.Z = MathHelper::Clamp(Value->Z, Min->Z, Max->Z);
		Result.W = MathHelper::Clamp(Value->W, Min->W, Max->W);
	}
	template<class T>
	inline void Vector4<T>::Distance(Vector4<T>* Value1, Vector4<T>* Value2, T & Result)
	{
		Vector4<T> TemporaryVector;
		Subtract(Value1, Value2, TemporaryVector);
		Result = TemporaryVector.GetLength();
	}
	template<class T>
	inline void Vector4<T>::DistanceSquared(Vector4<T>* Value1, Vector4<T>* Value2, T & Result)
	{
		Vector4<T> TemporaryVector;
		Subtract(Value1, Value2, TemporaryVector);
		Result = TemporaryVector.GetLengthSquared();
	}
	template<class T>
	inline void Vector4<T>::Divide(Vector4<T>* Value, T Divisor, Vector4<T>& Result)
	{
		Divisor = 1.0f / Divisor;
		Result.X = Value->X * Divisor;
		Result.Y = Value->Y * Divisor;
		Result.Z = Value->Z * Divisor;
		Result.W = Value->W * Divisor;
	}
	template<class T>
	inline void Vector4<T>::Divide(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>& Result)
	{
		Result.X = Value1->X / Value2->X;
		Result.Y = Value1->Y / Value2->Y;
		Result.Z = Value1->Z / Value2->Z;
		Result.W = Value1->W / Value2->W;
	}
	template<class T>
	inline void Vector4<T>::Dot(Vector4<T>* Value1, Vector4<T>* Value2, T & Result)
	{
		Result = Value1->X * Value2->X + Value1->Y * Value2->Y + Value1->Z * Value2->Z + Value1->W * Value2->W;
	}
	template<class T>
	inline void Vector4<T>::Hermite(Vector4<T>* Value1, Vector4<T>* Tangent1, Vector4<T>* Value2, Vector4<T>* Tangent2, T Amount, Vector4<T>& Result)
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
	inline void Vector4<T>::Lerp(Vector4<T>* Value1, Vector4<T>* Value2, T Amount, Vector4<T>& Result)
	{
		Result.X = MathHelper::Lerp(Value1->X, Value2->X, Amount);
		Result.Y = MathHelper::Lerp(Value1->Y, Value2->Y, Amount);
		Result.Z = MathHelper::Lerp(Value1->Z, Value2->Z, Amount);
		Result.W = MathHelper::Lerp(Value1->W, Value2->W, Amount);
	}
	template<class T>
	inline void Vector4<T>::Max(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>& Result)
	{
		Result.X = MathHelper::Max(Value1->X, Value2->X);
		Result.Y = MathHelper::Max(Value1->Y, Value2->Y);
		Result.Z = MathHelper::Max(Value1->Z, Value2->Z);
		Result.W = MathHelper::Max(Value1->W, Value2->W);
	}
	template<class T>
	inline void Vector4<T>::Min(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>& Result)
	{
		Result.X = MathHelper::Min(Value1->X, Value2->X);
		Result.Y = MathHelper::Min(Value1->Y, Value2->Y);
		Result.Z = MathHelper::Min(Value1->Z, Value2->Z);
		Result.W = MathHelper::Min(Value1->W, Value2->W);
	}
	template<class T>
	inline void Vector4<T>::Multiply(Vector4<T>* Value, T Multiplier, Vector4<T>& Result)
	{
		Result.X = Value->X * Multiplier;
		Result.Y = Value->Y * Multiplier;
		Result.Z = Value->Z * Multiplier;
		Result.W = Value->W * Multiplier;
	}
	template<class T>
	inline void Vector4<T>::Multiply(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>& Result)
	{
		Result.X = Value1->X * Value2->X;
		Result.Y = Value1->Y * Value2->Y;
		Result.Z = Value1->Z * Value2->Z;
		Result.W = Value1->W * Value2->W;
	}
	template<class T>
	inline void Vector4<T>::Negate(Vector4<T>* Value, Vector4<T>& Result)
	{
		Result.X = -Value->X;
		Result.Y = -Value->Y;
		Result.Z = -Value->Z;
		Result.W = -Value->W;
	}
	template<class T>
	inline void Vector4<T>::Reflect(Vector4<T>* Value, Vector4<T>* Normal, Vector4<T>& Result)
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
	inline void Vector4<T>::SmoothStep(Vector4<T>* Value1, Vector4<T>* Value2, T Amount, Vector4<T>& Result)
	{
		Result.X = MathHelper::SmoothStep(Value1->X, Value2->X, Amount);
		Result.Y = MathHelper::SmoothStep(Value1->Y, Value2->Y, Amount);
		Result.Z = MathHelper::SmoothStep(Value1->Z, Value2->Z, Amount);
		Result.W = MathHelper::SmoothStep(Value1->W, Value2->W, Amount);
	}
	template<class T>
	inline void Vector4<T>::Subtract(Vector4<T>* Value1, Vector4<T>* Value2, Vector4<T>& Result)
	{
		Result.X = Value1->X - Value2->X;
		Result.Y = Value1->Y - Value2->Y;
		Result.Z = Value1->Z - Value2->Z;
		Result.W = Value1->W - Value2->W;
	}
	*/
}
#endif
