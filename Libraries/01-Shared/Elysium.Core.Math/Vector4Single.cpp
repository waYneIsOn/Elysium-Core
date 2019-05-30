#include "Vector4Single.hpp"

Elysium::Core::Math::Numerics::Vector4Single::Vector4Single()
	: Elysium::Core::Math::Numerics::Vector4Template<float>()
{
}
Elysium::Core::Math::Numerics::Vector4Single::Vector4Single(float Value)
	: Elysium::Core::Math::Numerics::Vector4Template<float>(Value)
{
}
Elysium::Core::Math::Numerics::Vector4Single::Vector4Single(float ValueX, float ValueY, float ValueZ, float ValueW)
	: Elysium::Core::Math::Numerics::Vector4Template<float>(ValueX, ValueY, ValueZ, ValueW)
{
}
Elysium::Core::Math::Numerics::Vector4Single::~Vector4Single()
{
}

Elysium::Core::Math::Numerics::Vector4Single Elysium::Core::Math::Numerics::Vector4Single::One()
{
	return Vector4Single(1.0f);
}
Elysium::Core::Math::Numerics::Vector4Single Elysium::Core::Math::Numerics::Vector4Single::UnitX()
{
	return Vector4Single(1.0f, 0.0f, 0.0f, 0.0f);
}
Elysium::Core::Math::Numerics::Vector4Single Elysium::Core::Math::Numerics::Vector4Single::UnitY()
{
	return Vector4Single(0.0f, 1.0f, 0.0f, 0.0f);
}
Elysium::Core::Math::Numerics::Vector4Single Elysium::Core::Math::Numerics::Vector4Single::UnitZ()
{
	return Vector4Single(0.0f, 0.0f, 1.0f, 0.0f);
}
Elysium::Core::Math::Numerics::Vector4Single Elysium::Core::Math::Numerics::Vector4Single::UnitW()
{
	return Vector4Single(0.0f, 0.0f, 0.0f, 1.0f);
}
Elysium::Core::Math::Numerics::Vector4Single Elysium::Core::Math::Numerics::Vector4Single::Zero()
{
	return Vector4Single(0.0f);
}
