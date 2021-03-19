#include "MathHelper.hpp"

#ifndef _LIMITS_
#include <limits>
#endif

Elysium::Core::int16_t Elysium::Core::Math::Absolute(const Elysium::Core::int16_t Value)
{
	// http://www.graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
	const Elysium::Core::int16_t Mask = (Value >> sizeof(Elysium::Core::int16_t)) * CHAR_BIT - 1;
	return (Value + Mask) ^ Mask;
}

Elysium::Core::int32_t Elysium::Core::Math::Absolute(const Elysium::Core::int32_t Value)
{
	// http://www.graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
	const Elysium::Core::int32_t Mask = (Value >> sizeof(Elysium::Core::int32_t)) * CHAR_BIT - 1;
	return (Value + Mask) ^ Mask;
}

Elysium::Core::int64_t Elysium::Core::Math::Absolute(const Elysium::Core::int64_t Value)
{
	// http://www.graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
	const Elysium::Core::int64_t Mask = (Value >> sizeof(Elysium::Core::int64_t)) * CHAR_BIT - 1;
	return (Value + Mask) ^ Mask;
}

int Elysium::Core::Math::MathHelper::Absolute(const int Value)
{
	// http://www.graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
	const int Mask = (Value >> sizeof(int)) * CHAR_BIT - 1;
	return (Value + Mask) ^ Mask;
}
long Elysium::Core::Math::MathHelper::Absolute(const long Value)
{
	// http://www.graphics.stanford.edu/~seander/bithacks.html#IntegerAbs
	const long Mask = (Value >> sizeof(long)) * CHAR_BIT - 1;
	return (Value + Mask) ^ Mask;
}
float Elysium::Core::Math::MathHelper::Absolute(const float Value)
{
	return (Value < 0) ? -Value : Value;
}
double Elysium::Core::Math::MathHelper::Absolute(const double Value)
{
	return (Value < 0) ? -Value : Value;
}

double Elysium::Core::Math::MathHelper::Max(const double Value1, const double Value2)
{
	return (Value1 > Value2) ? Value1 : Value2;
}
float Elysium::Core::Math::MathHelper::Max(const float Value1, const float Value2)
{
	return (Value1 > Value2) ? Value1 : Value2;
}
size_t Elysium::Core::Math::MathHelper::Max(const size_t Value1, const size_t Value2)
{
	return (Value1 > Value2) ? Value1 : Value2;
}
Elysium::Core::uint32_t Elysium::Core::Math::MathHelper::Max(const uint32_t Value1, const uint32_t Value2)
{
	return (Value1 > Value2) ? Value1 : Value2;
}

double Elysium::Core::Math::MathHelper::Min(const double Value1, const double Value2)
{
	return (Value1 < Value2) ? Value1 : Value2;
}
float Elysium::Core::Math::MathHelper::Min(const float Value1, const float Value2)
{
	return (Value1 < Value2) ? Value1 : Value2;
}
size_t Elysium::Core::Math::MathHelper::Min(const size_t Value1, const size_t Value2)
{
	return (Value1 < Value2) ? Value1 : Value2;
}
Elysium::Core::uint32_t Elysium::Core::Math::MathHelper::Min(const uint32_t Value1, const uint32_t Value2)
{
	return (Value1 < Value2) ? Value1 : Value2;
}

double Elysium::Core::Math::MathHelper::Barycentric(const double Value1, const double Value2, const double Value3, const double Amount1, const double Amount2)
{
	return Value1 + (Value2 - Value1) * Amount1 + (Value3 - Value1) * Amount2;
}
float Elysium::Core::Math::MathHelper::Barycentric(const float Value1, const float Value2, const float Value3, const float Amount1, const float Amount2)
{
	return Value1 + (Value2 - Value1) * Amount1 + (Value3 - Value1) * Amount2;
}

double Elysium::Core::Math::MathHelper::CatmullRom(const double Value1, const double Value2, const double Value3, const double Value4, const double Amount)
{
	// http://www.mvps.org/directx/articles/catmull/
	// use double to not lose precission!
	double AmountSquared = Amount * Amount;
	double AmountCubed = AmountSquared * Amount;

	return CatmullRom(Value1, Value2, Value3, Value4, Amount, AmountSquared, AmountCubed);
}
float Elysium::Core::Math::MathHelper::CatmullRom(const float Value1, const float Value2, const float Value3, const float Value4, const float Amount)
{
	// http://www.mvps.org/directx/articles/catmull/
	// use double to not lose precission!
	double AmountSquared = Amount * Amount;
	double AmountCubed = AmountSquared * Amount;

	return CatmullRom(Value1, Value2, Value3, Value4, Amount, AmountSquared, AmountCubed);
}

double Elysium::Core::Math::MathHelper::CatmullRom(const double Value1, const double Value2, const double Value3, const double Value4, const double Amount, const double AmountSquared, const double AmountCubed)
{
	return (0.5 * (2.0 * Value2 +
		(Value3 - Value1) * Amount +
		(2.0 * Value1 - 5.0 * Value2 + 4.0 * Value3 - Value4) * AmountSquared +
		(3.0 * Value2 - Value1 - 3.0 * Value3 + Value4) * AmountCubed));
}

float Elysium::Core::Math::MathHelper::CatmullRom(const float Value1, const float Value2, const float Value3, const float Value4, const float Amount, const double AmountSquared, const double AmountCubed)
{
	return (float)(0.5 * (2.0 * Value2 +
		(Value3 - Value1) * Amount +
		(2.0 * Value1 - 5.0 * Value2 + 4.0 * Value3 - Value4) * AmountSquared +
		(3.0 * Value2 - Value1 - 3.0 * Value3 + Value4) * AmountCubed));
}

double Elysium::Core::Math::MathHelper::Clamp(double Value, const double Min, const double Max)
{
	Value = (Value > Max) ? Max : Value;
	Value = (Value < Min) ? Min : Value;
	return Value;
}
float Elysium::Core::Math::MathHelper::Clamp(float Value, float Min, float Max)
{
	Value = (Value > Max) ? Max : Value;
	Value = (Value < Min) ? Min : Value;
	return Value;
}

double Elysium::Core::Math::MathHelper::Distance(const double Value1, const double Value2)
{
	return Absolute(Value1 - Value2);
}
float Elysium::Core::Math::MathHelper::Distance(const float Value1, const float Value2)
{
	return Absolute(Value1 - Value2);
}

double Elysium::Core::Math::MathHelper::Hermite(double Value1, double Tangent1, double Value2, double Tangent2, double Amount)
{
	double AmountSquared = Amount * Amount;
	double AmountCubed = AmountSquared * Amount;
	double AmountCubedTrippled = AmountCubed + AmountCubed + AmountCubed;

	return Hermite(Value1, Tangent1, Value2, Tangent2, Amount, AmountSquared, AmountCubed, AmountCubedTrippled);
}
float Elysium::Core::Math::MathHelper::Hermite(float Value1, float Tangent1, float Value2, float Tangent2, float Amount)
{
	float AmountSquared = Amount * Amount;
	float AmountCubed = AmountSquared * Amount;
	float AmountCubedTrippled = AmountCubed + AmountCubed + AmountCubed;

	return Hermite(Value1, Tangent1, Value2, Tangent2, Amount, AmountSquared, AmountCubed, AmountCubedTrippled);
}

double Elysium::Core::Math::MathHelper::Hermite(double Value1, double Tangent1, double Value2, double Tangent2, double Amount, double AmountSquared, double AmountCubed, double AmountCubedTrippled)
{
	return (Value1 * (((AmountCubed + AmountCubed) - AmountCubedTrippled) + 1.0f)) +
		(Value2 * ((-2.0f * AmountCubed) + AmountCubedTrippled)) +
		(Tangent1 * ((AmountCubed - (AmountSquared + AmountSquared)) + Amount)) +
		(Tangent2 * (AmountCubed - AmountSquared));
}
float Elysium::Core::Math::MathHelper::Hermite(float Value1, float Tangent1, float Value2, float Tangent2, float Amount, float AmountSquared, float AmountCubed, float AmountCubedTrippled)
{
	return (Value1 * (((AmountCubed + AmountCubed) - AmountCubedTrippled) + 1.0f)) +
		(Value2 * ((-2.0f * AmountCubed) + AmountCubedTrippled)) +
		(Tangent1 * ((AmountCubed - (AmountSquared + AmountSquared)) + Amount)) +
		(Tangent2 * (AmountCubed - AmountSquared));
}

double Elysium::Core::Math::MathHelper::Lerp(double Value1, double Value2, double Amount)
{
	return Value1 + (Value2 - Value1) * Amount;
}
float Elysium::Core::Math::MathHelper::Lerp(float Value1, float Value2, float Amount)
{
	return Value1 + (Value2 - Value1) * Amount;
}

double Elysium::Core::Math::MathHelper::SmoothStep(double Value1, double Value2, double Amount)
{
	return Hermite(Value1, 0.0, Value2, 0.0, Clamp(Amount, 0.0, 1.0));
}
float Elysium::Core::Math::MathHelper::SmoothStep(float Value1, float Value2, float Amount)
{
	return Hermite(Value1, 0.0f, Value2, 0.0f, Clamp(Amount, 0.0f, 1.0f));
}
