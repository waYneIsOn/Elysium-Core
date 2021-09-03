/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONTEMPLATE
#define ELYSIUM_CORE_MATH_NUMERICS_QUATERNIONTEMPLATE

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

#ifndef ELYSIUM_CORE_MATH_NUMERICS_MATRIX3X3TEMPLATE
#include "Matrix3x3Template.hpp"
#endif

#ifndef ELYSIUM_CORE_MATH_NUMERICS_MATRIX4X4TEMPLATE
#include "Matrix4x4Template.hpp"
#endif

namespace Elysium::Core::Math::Numerics
{
	template <typename T>
	class QuaternionTemplate
	{
	public:
		// constructors & destructor
		QuaternionTemplate(T ValueX, T ValueY, T ValueZ, T ValueW);
		virtual ~QuaternionTemplate();

		// fields
		T X;
		T Y;
		T Z;
		T W;

		// methods
		void Conjugate();
		T GetLength();
		T GetLengthSquared();
		void Normalize();

		// static methods
		static void Add(QuaternionTemplate* Value1, QuaternionTemplate* Value2, QuaternionTemplate& Result);
		static void Concatenate(QuaternionTemplate* Value1, QuaternionTemplate* Value2, QuaternionTemplate& Result);
		static void CreateFromAxisAngle(Vector3<T>* Axis, T Angle, QuaternionTemplate& Result);
		static void CreateFromRotationMatrix(Matrix3x3Template<T>* Matrix, QuaternionTemplate& Result);
		static void CreateFromRotationMatrix(Matrix4x4Template<T>* Matrix, QuaternionTemplate& Result);
		static void CreateFromYawPitchRoll(T Yaw, T Pitch, T Roll, QuaternionTemplate& Result);
		static void Divide(QuaternionTemplate* Value1, QuaternionTemplate* Value2, QuaternionTemplate& Result);
		static void Divide(QuaternionTemplate* Value, T Divisor, QuaternionTemplate& Result);
		static void Dot(QuaternionTemplate* Value1, QuaternionTemplate* Value2, T& Result);
		static void Inverse(QuaternionTemplate* Value, QuaternionTemplate& Result);
		static void Lerp(QuaternionTemplate* Value1, QuaternionTemplate* Value2, T Amount, QuaternionTemplate& Result);
		static void Multiply(QuaternionTemplate* Value1, QuaternionTemplate* Value2, QuaternionTemplate& Result);
		static void Multiply(QuaternionTemplate* Value, T Multiplier, QuaternionTemplate& Result);
		static void Negate(QuaternionTemplate* Value, QuaternionTemplate& Result);
		static void Slerp(QuaternionTemplate* Value1, QuaternionTemplate* Value2, T Amount, QuaternionTemplate& Result);
		static void Subtract(QuaternionTemplate* Value1, QuaternionTemplate* Value2, QuaternionTemplate& Result);
	};

	template<typename T>
	inline QuaternionTemplate<T>::QuaternionTemplate(T ValueX, T ValueY, T ValueZ, T ValueW)
		: X(ValueX), Y(ValueY), Z(ValueZ), W(ValueW)
	{
	}
	template<typename T>
	inline QuaternionTemplate<T>::~QuaternionTemplate()
	{
	}

	template<typename T>
	inline void QuaternionTemplate<T>::Conjugate()
	{
		X = -X;
		Y = -Y;
		Z = -Z;
		// no W on purpose!
	}
	template<typename T>
	inline T QuaternionTemplate<T>::GetLength()
	{
		return (T)sqrt(X * X + Y * Y + Z * Z + W * W);
	}
	template<typename T>
	inline T QuaternionTemplate<T>::GetLengthSquared()
	{
		return (T)(X * X + Y * Y + Z * Z + W * W);
	}
	template<typename T>
	inline void QuaternionTemplate<T>::Normalize()
	{
		T Factor = (T)1.0 / GetLength();
		X *= Factor;
		Y *= Factor;
		Z *= Factor;
		W *= Factor;
	}

	template<typename T>
	inline void QuaternionTemplate<T>::Add(QuaternionTemplate * Value1, QuaternionTemplate * Value2, QuaternionTemplate & Result)
	{
		Result.X = Value1->X + Value2->X;
		Result.Y = Value1->Y + Value2->Y;
		Result.Z = Value1->Z + Value2->Z;
		Result.W = Value1->W + Value2->W;
	}
	template<typename T>
	inline void QuaternionTemplate<T>::Concatenate(QuaternionTemplate * Value1, QuaternionTemplate * Value2, QuaternionTemplate & Result)
	{
		Multiply(Value2, Value1, Result);
	}
	template<typename T>
	inline void QuaternionTemplate<T>::CreateFromAxisAngle(Vector3<T> * Axis, T Angle, QuaternionTemplate & Result)
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
	inline void QuaternionTemplate<T>::CreateFromRotationMatrix(Matrix3x3Template<T> * Matrix, QuaternionTemplate & Result)
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
	inline void QuaternionTemplate<T>::CreateFromRotationMatrix(Matrix4x4Template<T>* Matrix, QuaternionTemplate & Result)
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
	inline void QuaternionTemplate<T>::CreateFromYawPitchRoll(T Yaw, T Pitch, T Roll, QuaternionTemplate& Result)
	{
		Vector3<T> YawAxis = Vector3<T>((T)0, (T)1, (T)0);		// up
		Vector3<T> PitchAxis = Vector3<T>((T)1, (T)0, (T)0);	// right
		Vector3<T> RollAxis = Vector3<T>((T)0, (T)0, (T)1);		// backward

		QuaternionTemplate<T> YawQuaternion = QuaternionTemplate<T>((T)0, (T)0, (T)0, (T)0);
		QuaternionTemplate<T> PitchQuaternion = QuaternionTemplate<T>((T)0, (T)0, (T)0, (T)0);
		QuaternionTemplate<T> RollQuaternion = QuaternionTemplate<T>((T)0, (T)0, (T)0, (T)0);

		CreateFromAxisAngle(&YawAxis, Yaw, YawQuaternion);
		CreateFromAxisAngle(&PitchAxis, Pitch, PitchQuaternion);
		CreateFromAxisAngle(&RollAxis, Roll, RollQuaternion);

		Multiply(&YawQuaternion, &PitchQuaternion, Result);
		Multiply(&Result, &RollQuaternion, Result);
	}
	template<typename T>
	inline void QuaternionTemplate<T>::Divide(QuaternionTemplate* Value1, QuaternionTemplate* Value2, QuaternionTemplate& Result)
	{
		QuaternionTemplate<T> Factor = QuaternionTemplate<T>((T)0, (T)0, (T)0, (T)0);
		Inverse(Value2, Factor);
		Multiply(Value1, &Factor, Result);
	}
	template<typename T>
	inline void QuaternionTemplate<T>::Divide(QuaternionTemplate * Value, T Divisor, QuaternionTemplate & Result)
	{
		Divisor = (T)1 / Divisor;
		Result.X = Value->X * Divisor;
		Result.Y = Value->Y * Divisor;
		Result.Z = Value->Z * Divisor;
		Result.W = Value->W * Divisor;
	}
	template<typename T>
	inline void QuaternionTemplate<T>::Dot(QuaternionTemplate * Value1, QuaternionTemplate * Value2, T & Result)
	{
		Result = (Value1->X * Value2->X + Value1->Y * Value2->Y + Value1->Z * Value2->Z + Value1->W * Value2->W);
	}
	template<typename T>
	inline void QuaternionTemplate<T>::Inverse(QuaternionTemplate * Value, QuaternionTemplate & Result)
	{
		T InverseLength = (T)1 / Value->GetLengthSquared();

		Result.X = -Value->X * InverseLength;
		Result.Y = -Value->Y * InverseLength;
		Result.Z = -Value->Z * InverseLength;
		Result.W = -Value->W * InverseLength;
	}
	template<typename T>
	inline void QuaternionTemplate<T>::Lerp(QuaternionTemplate * Value1, QuaternionTemplate * Value2, T Amount, QuaternionTemplate & Result)
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
	inline void QuaternionTemplate<T>::Multiply(QuaternionTemplate * Value1, QuaternionTemplate * Value2, QuaternionTemplate & Result)
	{
		Result.X = Value1->W * Value2->X + Value1->X * Value2->W + Value1->Y * Value2->Z - Value1->Z * Value2->Y;
		Result.Y = Value1->W * Value2->Y - Value1->X * Value2->Z + Value1->Y * Value2->W + Value1->Z * Value2->X;
		Result.Z = Value1->W * Value2->Z + Value1->X * Value2->Y - Value1->Y * Value2->X - Value1->Z * Value2->W;
		Result.W = Value1->W * Value2->W - Value1->X * Value2->X - Value1->Y * Value2->Y + Value1->Z * Value2->Z;
	}
	template<typename T>
	inline void QuaternionTemplate<T>::Multiply(QuaternionTemplate * Value, T Multiplier, QuaternionTemplate & Result)
	{
		Result.X = Value->X * Multiplier;
		Result.Y = Value->Y * Multiplier;
		Result.Z = Value->Z * Multiplier;
		Result.W = Value->W * Multiplier;
	}
	template<typename T>
	inline void QuaternionTemplate<T>::Negate(QuaternionTemplate * Value, QuaternionTemplate & Result)
	{
		Result.X = -Value->X;
		Result.Y = -Value->Y;
		Result.Z = -Value->Z;
		Result.W = -Value->W;
	}
	template<typename T>
	inline void QuaternionTemplate<T>::Slerp(QuaternionTemplate * Value1, QuaternionTemplate * Value2, T Amount, QuaternionTemplate & Result)
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
	inline void QuaternionTemplate<T>::Subtract(QuaternionTemplate * Value1, QuaternionTemplate * Value2, QuaternionTemplate & Result)
	{
		Result.X = Value1->X - Value2->X;
		Result.Y = Value1->Y - Value2->Y;
		Result.Z = Value1->Z - Value2->Z;
		Result.W = Value1->W - Value2->W;
	}
}
#endif
