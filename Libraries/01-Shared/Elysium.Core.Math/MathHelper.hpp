#pragma once
/*
===========================================================================

Copyright (C) 2017 waYne (CAM)

===========================================================================
*/
#pragma once

#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#define ELYSIUM_CORE_MATH_MATHHELPER

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

namespace Elysium
{
	namespace Core
	{
		namespace Math
		{
			class ELYSIUM_CORE_MATH_API MathHelper
			{
			public:
				// constants
				/*
				public const float E = (float)Math.E;
				public const float Log10E = 0.4342945f;
				public const float Log2E = 1.442695f;
				public const float Pi = (float)Math.PI;
				public const float PiOver2 = (float)(Math.PI * 0.5);
				public const float PiOver4 = (float)(Math.PI * 0.25);
				public const float TwoPi = (float)(Math.PI + Math.PI);

				private const double OneEightyOverPi = 180.0 / Math.PI;
				private const double PiOverOneEighty = Math.PI / 180.0;
				*/

				// static methods
				static int Absolute(int Value);
				static long Absolute(long Value);
				static float Absolute(float Value);
				static double Absolute(double Value);

				static double Max(double Value1, double Value2);
				static float Max(float Value1, float Value2);

				static double Min(double Value1, double Value2);
				static float Min(float Value1, float Value2);
				static size_t Min(size_t Value1, size_t Value2);

				// static methods (algorithms)
				static double Barycentric(double Value1, double Value2, double Value3, double Amount1, double Amount2);
				static float Barycentric(float Value1, float Value2, float Value3, float Amount1, float Amount2);

				static double CatmullRom(double Value1, double Value2, double Value3, double Value4, double Amount);
				static float CatmullRom(float Value1, float Value2, float Value3, float Value4, float Amount);

				static double CatmullRom(double Value1, double Value2, double Value3, double Value4, double Amount, double AmountSquared, double AmountCubed);
				static float CatmullRom(float Value1, float Value2, float Value3, float Value4, float Amount, double AmountSquared, double AmountCubed);

				static double Clamp(double Value, double Min, double Max);
				static float Clamp(float Value, float Min, float Max);

				static double Distance(double Value1, double Value2);
				static float Distance(float Value1, float Value2);

				static double Hermite(double Value1, double Tangent1, double Value2, double Tangent2, double Amount);
				static float Hermite(float Value1, float Tangent1, float Value2, float Tangent2, float Amount);

				static double Hermite(double Value1, double Tangent1, double Value2, double Tangent2, double Amount, double AmountSquared, double AmountCubed, double AmountCubedTrippled);
				static float Hermite(float Value1, float Tangent1, float Value2, float Tangent2, float Amount, float AmountSquared, float AmountCubed, float AmountCubedTrippled);

				static double Lerp(double Value1, double Value2, double Amount);
				static float Lerp(float Value1, float Value2, float Amount);

				static double SmoothStep(double Value1, double Value2, double Amount);
				static float SmoothStep(float Value1, float Value2, float Amount);
			};
		}
	}
}
#endif
