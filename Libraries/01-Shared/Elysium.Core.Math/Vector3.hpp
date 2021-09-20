/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3
#define ELYSIUM_CORE_MATH_NUMERICS_VECTOR3

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
	class Vector3 final
	{
	public:
		Vector3();
		Vector3(T Value);
		Vector3(T ValueX, T ValueY, T ValueZ);
		Vector3(const Vector3& Source);
		Vector3(Vector3&& Right) noexcept;
		~Vector3();

		Vector3<T>& operator=(const Vector3& Source);
		Vector3<T>& operator=(Vector3&& Right) noexcept;

		static Vector3<T> Zero();
		static Vector3<T> One();

		static Vector3<T> UnitX();
		static Vector3<T> UnitY();
		static Vector3<T> UnitZ();

		static Vector3<T> Backward();
		static Vector3<T> Down();
		static Vector3<T> Forward();
		static Vector3<T> Left();
		static Vector3<T> Right();
		static Vector3<T> Up();

		T X;
		T Y;
		T Z;

		T GetLength();
		T GetLengthSquared();
		void Normalize();
		/*
		static void Add(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>& Result);
		static void Barycentric(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>* Value3, T Amount1, T Amount2, Vector3<T>& Result);
		static void CatmullRom(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>* Value3, Vector3<T>* Value4, T Amount, Vector3<T>& Result);
		static void Clamp(Vector3<T>* Value, Vector3<T>* Min, Vector3<T>* Max, Vector3<T>& Result);
		static void Distance(Vector3<T>* Value1, Vector3<T>* Value2, T& Result);
		static void DistanceSquared(Vector3<T>* Value1, Vector3<T>* Value2, T& Result);
		static void Divide(Vector3<T>* Value, T Divisor, Vector3<T>& Result);
		static void Divide(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>& Result);
		static void Dot(Vector3<T>* Value1, Vector3<T>* Value2, T& Result);
		static void Hermite(Vector3<T>* Value1, Vector3<T>* Tangent1, Vector3<T>* Value2, Vector3<T>* Tangent2, T Amount, Vector3<T>& Result);
		static void Lerp(Vector3<T>* Value1, Vector3<T>* Value2, T Amount, Vector3<T>& Result);
		static void Max(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>& Result);
		static void Min(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>& Result);
		static void Multiply(Vector3<T>* Value, T Multiplier, Vector3<T>& Result);
		static void Multiply(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>& Result);
		static void Negate(Vector3<T>* Value, Vector3<T>& Result);
		static void Reflect(Vector3<T>* Value, Vector3<T>* Normal, Vector3<T>& Result);
		static void SmoothStep(Vector3<T>* Value1, Vector3<T>* Value2, T Amount, Vector3<T>& Result);
		static void Subtract(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>& Result);
		//static void Transform(Vector3<T>* Position, Matrix* Matrix, Vector3<T>& Result);
		//static void TransformNormal(Vector3<T>* Normal, Matrix* Matrix, Vector3<T>* Result);
		*/
	};

	template<class T>
	inline Vector3<T>::Vector3()
		: X(0), Y(0), Z(0)
	{ }
	template<class T>
	inline Vector3<T>::Vector3(T Value)
		: X(Value), Y(Value), Z(Value)
	{ }
	template<class T>
	inline Vector3<T>::Vector3(T ValueX, T ValueY, T ValueZ)
		: X(ValueX), Y(ValueY), Z(ValueZ)
	{ }
	template<class T>
	inline Vector3<T>::Vector3(const Vector3 & Source)
		: X(Source.X), Y(Source.Y), Z(Source.Z)
	{ }
	template<class T>
	inline Vector3<T>::Vector3(Vector3&& Right) noexcept
	{
		*this = Elysium::Core::Template::Functional::Move(Right);
	}
	template<class T>
	inline Vector3<T>::~Vector3()
	{ }

	template<class T>
	inline Vector3<T>& Vector3<T>::operator=(const Vector3 & Source)
	{
		if (this != &Source)
		{
			X = Source.X;
			Y = Source.Y;
			Z = Source.Z;
		}
		return *this;
	}

	template<class T>
	inline Vector3<T>& Vector3<T>::operator=(Vector3&& Right) noexcept
	{
		if (this != &Right)
		{
			X = Elysium::Core::Template::Functional::Move(Right.X);
			Y = Elysium::Core::Template::Functional::Move(Right.Y);
			Z = Elysium::Core::Template::Functional::Move(Right.Z);
		}
		return *this;
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Zero()
	{
		return Vector3<T>(static_cast<T>(0));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::One()
	{
		return Vector3<T>(static_cast<T>(1));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::UnitX()
	{
		return Vector3<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::UnitY()
	{
		return Vector3<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::UnitZ()
	{
		return Vector3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Backward()
	{
		return Vector3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Down()
	{
		return Vector3<T>(static_cast<T>(0), static_cast<T>(-1), static_cast<T>(0));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Forward()
	{
		return Vector3<T>(static_cast<T>(0), static_cast<T>(0), static_cast<T>(-1));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Left()
	{
		return Vector3<T>(static_cast<T>(-1), static_cast<T>(0), static_cast<T>(0));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Right()
	{
		return Vector3<T>(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0));
	}

	template<class T>
	inline Vector3<T> Vector3<T>::Up()
	{
		return Vector3<T>(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0));
	}

	template<class T>
	inline T Vector3<T>::GetLength()
	{
		return (T)sqrt(X * X + Y * Y + Z * Z);
	}
	template<class T>
	inline T Vector3<T>::GetLengthSquared()
	{
		return X * X + Y * Y + Z * Z;
	}
	template<class T>
	inline void Vector3<T>::Normalize()
	{
		T Factor = 1.0f / GetLength();
		X *= Factor;
		Y *= Factor;
		Z *= Factor;
	}
	/*
	template<class T>
	inline void Vector3<T>::Add(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>& Result)
	{
		Result.X = Value1->X + Value2->X;
		Result.Y = Value1->Y + Value2->Y;
		Result.Z = Value1->Z + Value2->Z;
	}
	template<class T>
	inline void Vector3<T>::Barycentric(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>* Value3, T Amount1, T Amount2, Vector3<T>& Result)
	{
		Result.X = MathHelper::Barycentric(Value1->X, Value2->X, Value3->X, Amount1, Amount2);
		Result.Y = MathHelper::Barycentric(Value1->Y, Value2->Y, Value3->Y, Amount1, Amount2);
		Result.Z = MathHelper::Barycentric(Value1->Z, Value2->Z, Value3->Z, Amount1, Amount2);
	}
	template<class T>
	inline void Vector3<T>::CatmullRom(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>* Value3, Vector3<T>* Value4, T Amount, Vector3<T>& Result)
	{
		// using double to not lose precission
		double AmountSquared = Amount * Amount;
		double AmountCubed = AmountSquared * Amount;

		Result.X = MathHelper::CatmullRom(Value1->X, Value2->X, Value3->X, Value4->X, Amount, AmountSquared, AmountCubed);
		Result.Y = MathHelper::CatmullRom(Value1->Y, Value2->Y, Value3->Y, Value4->Y, Amount, AmountSquared, AmountCubed);
		Result.Z = MathHelper::CatmullRom(Value1->Z, Value2->Z, Value3->Z, Value4->Z, Amount, AmountSquared, AmountCubed);
	}
	template<class T>
	inline void Vector3<T>::Clamp(Vector3<T>* Value, Vector3<T>* Min, Vector3<T>* Max, Vector3<T>& Result)
	{
		Result.X = MathHelper::Clamp(Value->X, Min->X, Max->X);
		Result.Y = MathHelper::Clamp(Value->Y, Min->Y, Max->Y);
		Result.Z = MathHelper::Clamp(Value->Z, Min->Z, Max->Z);
	}
	template<class T>
	inline void Vector3<T>::Distance(Vector3<T>* Value1, Vector3<T>* Value2, T & Result)
	{
		Vector3<T> TemporaryVector;
		Subtract(Value1, Value2, TemporaryVector);
		Result = TemporaryVector.GetLength();
	}
	template<class T>
	inline void Vector3<T>::DistanceSquared(Vector3<T>* Value1, Vector3<T>* Value2, T & Result)
	{
		Vector3<T> TemporaryVector;
		Subtract(Value1, Value2, TemporaryVector);
		Result = TemporaryVector.GetLengthSquared();
	}
	template<class T>
	inline void Vector3<T>::Divide(Vector3<T>* Value, T Divisor, Vector3<T>& Result)
	{
		Divisor = 1.0f / Divisor;
		Result.X = Value->X * Divisor;
		Result.Y = Value->Y * Divisor;
		Result.Z = Value->Z * Divisor;
	}
	template<class T>
	inline void Vector3<T>::Divide(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>& Result)
	{
		Result.X = Value1->X / Value2->X;
		Result.Y = Value1->Y / Value2->Y;
		Result.Z = Value1->Z / Value2->Z;
	}
	template<class T>
	inline void Vector3<T>::Dot(Vector3<T>* Value1, Vector3<T>* Value2, T & Result)
	{
		Result = Value1->X * Value2->X + Value1->Y * Value2->Y + Value1->Z * Value2->Z;
	}
	template<class T>
	inline void Vector3<T>::Hermite(Vector3<T>* Value1, Vector3<T>* Tangent1, Vector3<T>* Value2, Vector3<T>* Tangent2, T Amount, Vector3<T>& Result)
	{
		T AmountSquared = Amount * Amount;
		T AmountCubed = AmountSquared * Amount;
		T AmountCubedTimesThree = AmountSquared + AmountSquared + AmountSquared;

		Result.X = MathHelper::Hermite(Value1->X, Tangent1->X, Value2->X, Tangent2->X, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
		Result.Y = MathHelper::Hermite(Value1->Y, Tangent1->Y, Value2->Y, Tangent2->Y, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
		Result.Z = MathHelper::Hermite(Value1->Z, Tangent1->Z, Value2->Z, Tangent2->Z, Amount, AmountSquared, AmountCubed, AmountCubedTimesThree);
	}
	template<class T>
	inline void Vector3<T>::Lerp(Vector3<T>* Value1, Vector3<T>* Value2, T Amount, Vector3<T>& Result)
	{
		Result.X = MathHelper::Lerp(Value1->X, Value2->X, Amount);
		Result.Y = MathHelper::Lerp(Value1->Y, Value2->Y, Amount);
		Result.Z = MathHelper::Lerp(Value1->Z, Value2->Z, Amount);
	}
	template<class T>
	inline void Vector3<T>::Max(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>& Result)
	{
		Result.X = MathHelper::Max(Value1->X, Value2->X);
		Result.Y = MathHelper::Max(Value1->Y, Value2->Y);
		Result.Z = MathHelper::Max(Value1->Z, Value2->Z);
	}
	template<class T>
	inline void Vector3<T>::Min(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>& Result)
	{
		Result.X = MathHelper::Min(Value1->X, Value2->X);
		Result.Y = MathHelper::Min(Value1->Y, Value2->Y);
		Result.Z = MathHelper::Min(Value1->Z, Value2->Z);
	}
	template<class T>
	inline void Vector3<T>::Multiply(Vector3<T>* Value, T Multiplier, Vector3<T>& Result)
	{
		Result.X = Value->X * Multiplier;
		Result.Y = Value->Y * Multiplier;
		Result.Z = Value->Z * Multiplier;
	}
	template<class T>
	inline void Vector3<T>::Multiply(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>& Result)
	{
		Result.X = Value1->X * Value2->X;
		Result.Y = Value1->Y * Value2->Y;
		Result.Z = Value1->Z * Value2->Z;
	}
	template<class T>
	inline void Vector3<T>::Negate(Vector3<T>* Value, Vector3<T>& Result)
	{
		Result.X = -Value->X;
		Result.Y = -Value->Y;
		Result.Z = -Value->Z;
	}
	template<class T>
	inline void Vector3<T>::Reflect(Vector3<T>* Value, Vector3<T>* Normal, Vector3<T>& Result)
	{
		T Factor = 1.0f;
		Dot(Value, Normal, Factor);
		Factor *= 2;

		Result.X = Value->X - (Factor * Normal->X);
		Result.Y = Value->Y - (Factor * Normal->Y);
		Result.Z = Value->Z - (Factor * Normal->Z);
	}
	template<class T>
	inline void Vector3<T>::SmoothStep(Vector3<T>* Value1, Vector3<T>* Value2, T Amount, Vector3<T>& Result)
	{
		Result.X = MathHelper::SmoothStep(Value1->X, Value2->X, Amount);
		Result.Y = MathHelper::SmoothStep(Value1->Y, Value2->Y, Amount);
		Result.Z = MathHelper::SmoothStep(Value1->Z, Value2->Z, Amount);
	}
	template<class T>
	inline void Vector3<T>::Subtract(Vector3<T>* Value1, Vector3<T>* Value2, Vector3<T>& Result)
	{
		Result.X = Value1->X - Value2->X;
		Result.Y = Value1->Y - Value2->Y;
		Result.Z = Value1->Z - Value2->Z;
	}
	*/
}
#endif
