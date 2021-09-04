/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_QUATERNION
#define ELYSIUM_CORE_MATH_NUMERICS_QUATERNION

#ifdef _MSC_VER
#pragma once
#endif

#ifndef _INC_MATH
#include <math.h>
#endif

#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#include "MathHelper.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_VECTOR3
#include "Vector3.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_MATRIX3X3
#include "Matrix3x3.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_MATRIX4X4
#include "Matrix4x4.hpp"
#endif

#ifndef ELYSIUM_CORE_TEMPLATE_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	template <typename T>
	class Quaternion final
	{
	public:
		Quaternion(const T ValueX, const T ValueY, const T ValueZ, const T ValueW);
		Quaternion(const Quaternion& Source);
		Quaternion(Quaternion&& Right) noexcept;
		~Quaternion();

		Quaternion<T>& operator=(const Quaternion& Source);
		Quaternion<T>& operator=(Quaternion&& Right) noexcept;

		T X;
		T Y;
		T Z;
		T W;

		void Conjugate();
		T GetLength();
		T GetLengthSquared();
		void Normalize();

		static void Add(Quaternion<T>* Value1, Quaternion<T>* Value2, Quaternion<T>& Result);
		static void Concatenate(Quaternion<T>* Value1, Quaternion<T>* Value2, Quaternion<T>& Result);
		static void CreateFromAxisAngle(Vector3<T>* Axis, T Angle, Quaternion<T>& Result);
		static void CreateFromRotationMatrix(Matrix3x3<T>* Matrix, Quaternion<T>& Result);
		static void CreateFromRotationMatrix(Matrix4x4<T>* Matrix, Quaternion<T>& Result);
		static void CreateFromYawPitchRoll(T Yaw, T Pitch, T Roll, Quaternion<T>& Result);
		static void Divide(Quaternion<T>* Value1, Quaternion<T>* Value2, Quaternion<T>& Result);
		static void Divide(Quaternion<T>* Value, T Divisor, Quaternion<T>& Result);
		static void Dot(Quaternion<T>* Value1, Quaternion<T>* Value2, T& Result);
		static void Inverse(Quaternion<T>* Value, Quaternion<T>& Result);
		static void Lerp(Quaternion<T>* Value1, Quaternion<T>* Value2, T Amount, Quaternion<T>& Result);
		static void Multiply(Quaternion<T>* Value1, Quaternion<T>* Value2, Quaternion<T>& Result);
		static void Multiply(Quaternion<T>* Value, T Multiplier, Quaternion<T>& Result);
		static void Negate(Quaternion<T>* Value, Quaternion<T>& Result);
		static void Slerp(Quaternion<T>* Value1, Quaternion<T>* Value2, T Amount, Quaternion<T>& Result);
		static void Subtract(Quaternion<T>* Value1, Quaternion<T>* Value2, Quaternion<T>& Result);
	};

	template<typename T>
	inline Quaternion<T>::Quaternion(const T ValueX, const T ValueY, const T ValueZ, const T ValueW)
		: X(ValueX), Y(ValueY), Z(ValueZ), W(ValueW)
	{ }
	template<typename T>
	inline Quaternion<T>::Quaternion(const Quaternion& Source)
		: X(Source.X), Y(Source.Y), Z(Source.Z), W(Source.W)
	{ }
	template<typename T>
	inline Quaternion<T>::Quaternion(Quaternion&& Right) noexcept
	{
		*this = Elysium::Core::Template::Move(Right);
	}
	template<typename T>
	inline Quaternion<T>::~Quaternion()
	{ }

	template<typename T>
	inline Quaternion<T>& Quaternion<T>::operator=(const Quaternion& Source)
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
	inline Quaternion<T>& Quaternion<T>::operator=(Quaternion&& Right) noexcept
	{
		if (this != &Right)
		{
			X = Elysium::Core::Template::Move(Right.X);
			Y = Elysium::Core::Template::Move(Right.Y);
			Z = Elysium::Core::Template::Move(Right.Z);
			W = Elysium::Core::Template::Move(Right.W);
		}
		return *this;
	}

	template<typename T>
	inline void Quaternion<T>::Conjugate()
	{
		X = -X;
		Y = -Y;
		Z = -Z;
		// no W on purpose!
	}
	template<typename T>
	inline T Quaternion<T>::GetLength()
	{
		return (T)sqrt(X * X + Y * Y + Z * Z + W * W);
	}
	template<typename T>
	inline T Quaternion<T>::GetLengthSquared()
	{
		return (T)(X * X + Y * Y + Z * Z + W * W);
	}
	template<typename T>
	inline void Quaternion<T>::Normalize()
	{
		T Factor = (T)1.0 / GetLength();
		X *= Factor;
		Y *= Factor;
		Z *= Factor;
		W *= Factor;
	}

	template<typename T>
	inline void Quaternion<T>::Add(Quaternion<T>* Value1, Quaternion<T>* Value2, Quaternion<T>& Result)
	{
		Result.X = Value1->X + Value2->X;
		Result.Y = Value1->Y + Value2->Y;
		Result.Z = Value1->Z + Value2->Z;
		Result.W = Value1->W + Value2->W;
	}
	template<typename T>
	inline void Quaternion<T>::Concatenate(Quaternion<T>* Value1, Quaternion<T>* Value2, Quaternion<T>& Result)
	{
		Multiply(Value2, Value1, Result);
	}
	template<typename T>
	inline void Quaternion<T>::CreateFromAxisAngle(Vector3<T> * Axis, T Angle, Quaternion<T>& Result)
	{
		Angle *= 0.5f;
		T SinusAngle = (T)sin(Angle);
		T CosinusAngle = (T)cos(Angle);

		Result.X = Axis->X * SinusAngle;
		Result.Y = Axis->Y * SinusAngle;
		Result.Z = Axis->Z * SinusAngle;
		Result.W = CosinusAngle;
	}
	template<typename T>
	inline void Quaternion<T>::CreateFromRotationMatrix(Matrix3x3<T> * Matrix, Quaternion<T>& Result)
	{
		T Trace = Matrix->M11 + Matrix->M22 + Matrix->M33;	// trace = sum of the leading diagonal terms
		if (Trace > (T)0)
		{
			T S = (T)sqrt(Trace + (T)1);
			Result.W = S * (T)0.5;
			S = (T)0.5 / S;
			Result.X = (Matrix->M23 - Matrix->M32) * S;
			Result.Y = (Matrix->M31 - Matrix->M13) * S;
			Result.Z = (Matrix->M12 - Matrix->M21) * S;
		}
		else if ((Matrix->M11 >= Matrix->M22) && (Matrix->M11 >= Matrix->M33))
		{
			T S = (T)sqrt((T)1 + Matrix->M11 - Matrix->M22 - Matrix->M33);
			T S2 = (T)0.5 / S;
			Result.X = (T)0.5 * S;
			Result.Y = (Matrix->M12 + Matrix->M21) * S2;
			Result.Z = (Matrix->M13 + Matrix->M31) * S2;
			Result.W = (Matrix->M23 + Matrix->M32) * S2;
		}
		else if (Matrix->M22 > Matrix->M33)
		{
			T S = (T)sqrt((T)1 + Matrix->M22 - Matrix->M11 - Matrix->M33);
			T S2 = (T)0.5 / S;
			Result.X = (Matrix->M21 + Matrix->M12) * S2;
			Result.Y = (T)0.5 * S;
			Result.Z = (Matrix->M32 + Matrix->M23) * S2;
			Result.W = (Matrix->M31 - Matrix->M13) * S2;
		}
		else
		{
			T S = (T)sqrt((T)1 + Matrix->M22 - Matrix->M11 - Matrix->M33);
			T S2 = (T)0.5 / S;
			Result.X = (Matrix->M21 + Matrix->M12) * S2;
			Result.Y = (T)0.5 * S;
			Result.Z = (Matrix->M32 + Matrix->M23) * S2;
			Result.W = (Matrix->M12 + Matrix->M21) * S2;
		}
	}
	template<typename T>
	inline void Quaternion<T>::CreateFromRotationMatrix(Matrix4x4<T>* Matrix, Quaternion<T>& Result)
	{
		T Trace = Matrix->M11 + Matrix->M22 + Matrix->M33;	// trace = sum of the leading diagonal terms
		if (Trace > (T)0)
		{
			T S = (T)sqrt(Trace + (T)1);
			Result.W = S * (T)0.5;
			S = (T)0.5 / S;
			Result.X = (Matrix->M23 - Matrix->M32) * S;
			Result.Y = (Matrix->M31 - Matrix->M13) * S;
			Result.Z = (Matrix->M12 - Matrix->M21) * S;
		}
		else if ((Matrix->M11 >= Matrix->M22) && (Matrix->M11 >= Matrix->M33))
		{
			T S = (T)sqrt((T)1 + Matrix->M11 - Matrix->M22 - Matrix->M33);
			T S2 = (T)0.5 / S;
			Result.X = (T)0.5 * S;
			Result.Y = (Matrix->M12 + Matrix->M21) * S2;
			Result.Z = (Matrix->M13 + Matrix->M31) * S2;
			Result.W = (Matrix->M23 + Matrix->M32) * S2;
		}
		else if (Matrix->M22 > Matrix->M33)
		{
			T S = (T)sqrt((T)1 + Matrix->M22 - Matrix->M11 - Matrix->M33);
			T S2 = (T)0.5 / S;
			Result.X = (Matrix->M21 + Matrix->M12) * S2;
			Result.Y = (T)0.5 * S;
			Result.Z = (Matrix->M32 + Matrix->M23) * S2;
			Result.W = (Matrix->M31 - Matrix->M13) * S2;
		}
		else
		{
			T S = (T)sqrt((T)1 + Matrix->M22 - Matrix->M11 - Matrix->M33);
			T S2 = (T)0.5 / S;
			Result.X = (Matrix->M21 + Matrix->M12) * S2;
			Result.Y = (T)0.5 * S;
			Result.Z = (Matrix->M32 + Matrix->M23) * S2;
			Result.W = (Matrix->M12 + Matrix->M21) * S2;
		}
	}
	template<typename T>
	inline void Quaternion<T>::CreateFromYawPitchRoll(T Yaw, T Pitch, T Roll, Quaternion<T>& Result)
	{
		Vector3<T> YawAxis = Vector3<T>((T)0, (T)1, (T)0);		// up
		Vector3<T> PitchAxis = Vector3<T>((T)1, (T)0, (T)0);	// right
		Vector3<T> RollAxis = Vector3<T>((T)0, (T)0, (T)1);		// backward

		Quaternion<T> YawQuaternion = Quaternion<T>((T)0, (T)0, (T)0, (T)0);
		Quaternion<T> PitchQuaternion = Quaternion<T>((T)0, (T)0, (T)0, (T)0);
		Quaternion<T> RollQuaternion = Quaternion<T>((T)0, (T)0, (T)0, (T)0);

		CreateFromAxisAngle(&YawAxis, Yaw, YawQuaternion);
		CreateFromAxisAngle(&PitchAxis, Pitch, PitchQuaternion);
		CreateFromAxisAngle(&RollAxis, Roll, RollQuaternion);

		Multiply(&YawQuaternion, &PitchQuaternion, Result);
		Multiply(&Result, &RollQuaternion, Result);
	}
	template<typename T>
	inline void Quaternion<T>::Divide(Quaternion<T>* Value1, Quaternion<T>* Value2, Quaternion<T>& Result)
	{
		Quaternion<T> Factor = Quaternion<T>((T)0, (T)0, (T)0, (T)0);
		Inverse(Value2, Factor);
		Multiply(Value1, &Factor, Result);
	}
	template<typename T>
	inline void Quaternion<T>::Divide(Quaternion<T>* Value, T Divisor, Quaternion<T>& Result)
	{
		Divisor = (T)1 / Divisor;
		Result.X = Value->X * Divisor;
		Result.Y = Value->Y * Divisor;
		Result.Z = Value->Z * Divisor;
		Result.W = Value->W * Divisor;
	}
	template<typename T>
	inline void Quaternion<T>::Dot(Quaternion<T>* Value1, Quaternion<T>* Value2, T & Result)
	{
		Result = (Value1->X * Value2->X + Value1->Y * Value2->Y + Value1->Z * Value2->Z + Value1->W * Value2->W);
	}
	template<typename T>
	inline void Quaternion<T>::Inverse(Quaternion<T>* Value, Quaternion<T>& Result)
	{
		T InverseLength = (T)1 / Value->GetLengthSquared();

		Result.X = -Value->X * InverseLength;
		Result.Y = -Value->Y * InverseLength;
		Result.Z = -Value->Z * InverseLength;
		Result.W = -Value->W * InverseLength;
	}
	template<typename T>
	inline void Quaternion<T>::Lerp(Quaternion<T>* Value1, Quaternion<T>* Value2, T Amount, Quaternion<T>& Result)
	{
		T DotProduct;
		Dot(Value1, Value2, DotProduct);
		T AmountDifference = (T)1 - Amount;
		if (DotProduct < (T)0)
		{
			Amount = -Amount;
		}

		Result.X = AmountDifference * Value1->X + Amount * Value2->X;
		Result.Y = AmountDifference * Value1->Y + Amount * Value2->Y;
		Result.Z = AmountDifference * Value1->Z + Amount * Value2->Z;
		Result.W = AmountDifference * Value1->W + Amount * Value2->W;
		Result.Normalize();
	}
	template<typename T>
	inline void Quaternion<T>::Multiply(Quaternion<T>* Value1, Quaternion<T>* Value2, Quaternion<T>& Result)
	{
		Result.X = Value1->W * Value2->X + Value1->X * Value2->W + Value1->Y * Value2->Z - Value1->Z * Value2->Y;
		Result.Y = Value1->W * Value2->Y - Value1->X * Value2->Z + Value1->Y * Value2->W + Value1->Z * Value2->X;
		Result.Z = Value1->W * Value2->Z + Value1->X * Value2->Y - Value1->Y * Value2->X - Value1->Z * Value2->W;
		Result.W = Value1->W * Value2->W - Value1->X * Value2->X - Value1->Y * Value2->Y + Value1->Z * Value2->Z;
	}
	template<typename T>
	inline void Quaternion<T>::Multiply(Quaternion<T>* Value, T Multiplier, Quaternion<T>& Result)
	{
		Result.X = Value->X * Multiplier;
		Result.Y = Value->Y * Multiplier;
		Result.Z = Value->Z * Multiplier;
		Result.W = Value->W * Multiplier;
	}
	template<typename T>
	inline void Quaternion<T>::Negate(Quaternion<T>* Value, Quaternion<T>& Result)
	{
		Result.X = -Value->X;
		Result.Y = -Value->Y;
		Result.Z = -Value->Z;
		Result.W = -Value->W;
	}
	template<typename T>
	inline void Quaternion<T>::Slerp(Quaternion<T>* Value1, Quaternion<T>* Value2, T Amount, Quaternion<T>& Result)
	{
		T CosinusAlpha;
		Dot(Value1, Value2, CosinusAlpha);

		T Alpha = (T)acos(CosinusAlpha);
		T InverseSinusAlphaInverse = (T)1 / (T)sin(Alpha);

		T Amount1 = (T)sin(((T)1 - Amount) * Alpha) * InverseSinusAlphaInverse;
		T Amount2 = (T)sin(Amount * Alpha) * InverseSinusAlphaInverse;

		Result.X = Value1->X * Amount1 + Value2->X * Amount2;
		Result.Y = Value1->Y * Amount1 + Value2->Y * Amount2;
		Result.Z = Value1->Z * Amount1 + Value2->Z * Amount2;
		Result.W = Value1->W * Amount1 + Value2->W * Amount2;
	}
	template<typename T>
	inline void Quaternion<T>::Subtract(Quaternion<T>* Value1, Quaternion<T>* Value2, Quaternion<T>& Result)
	{
		Result.X = Value1->X - Value2->X;
		Result.Y = Value1->Y - Value2->Y;
		Result.Z = Value1->Z - Value2->Z;
		Result.W = Value1->W - Value2->W;
	}
}
#endif
