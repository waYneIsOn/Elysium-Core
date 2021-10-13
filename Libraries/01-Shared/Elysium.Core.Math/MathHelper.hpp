/*
===========================================================================

Copyright (c) waYne (CAM). All rights reserved.

===========================================================================
*/
#ifndef ELYSIUM_CORE_MATH_MATHHELPER
#define ELYSIUM_CORE_MATH_MATHHELPER

#ifdef _MSC_VER
#pragma once
#endif

#ifndef ELYSIUM_CORE_MATH_API
#include "API.hpp"
#endif

#ifndef ELYSIUM_CORE_INTEGER
#include "../Elysium.Core/Integer.hpp"
#endif

namespace Elysium::Core::Math
{
	Elysium::Core::int16_t Absolute(const Elysium::Core::int16_t Value);
	Elysium::Core::int32_t Absolute(const Elysium::Core::int32_t Value);
	Elysium::Core::int64_t Absolute(const Elysium::Core::int64_t Value);

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
		static int Absolute(const int Value);
		static long Absolute(const long Value);
		static float Absolute(const float Value);
		static double Absolute(const double Value);

		static double Max(const double Value1, const double Value2);
		static float Max(const float Value1, const float Value2);
		static Elysium::Core::size Max(const Elysium::Core::size Value1, const Elysium::Core::size Value2);
		static uint32_t Max(const uint32_t Value1, const uint32_t Value2);

		static double Min(const double Value1, const  double Value2);
		static float Min(const float Value1, const float Value2);
		static Elysium::Core::size Min(const Elysium::Core::size Value1, const Elysium::Core::size Value2);
		static uint32_t Min(const uint32_t Value1, const uint32_t Value2);

		// static methods (algorithms)
		static double Barycentric(const double Value1, const double Value2, const double Value3, const double Amount1, const double Amount2);
		static float Barycentric(const float Value1, const float Value2, const float Value3, const float Amount1, const float Amount2);

		static double CatmullRom(const double Value1, const double Value2, const double Value3, const double Value4, const double Amount);
		static float CatmullRom(const float Value1, const float Value2, const float Value3, const float Value4, const float Amount);

		static double CatmullRom(const double Value1, const double Value2, const double Value3, const double Value4, const double Amount, const double AmountSquared, const double AmountCubed);
		static float CatmullRom(const float Value1, const float Value2, const float Value3, const float Value4, const float Amount, const double AmountSquared, const double AmountCubed);

		static double Clamp(double Value, double Min, double Max);
		static float Clamp(float Value, float Min, float Max);

		static double Distance(const double Value1, const double Value2);
		static float Distance(const float Value1, const float Value2);

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
#endif
