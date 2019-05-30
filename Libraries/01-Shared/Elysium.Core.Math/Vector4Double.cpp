#include "Vector4Double.hpp"

Elysium::Core::Math::Numerics::Vector4Double::Vector4Double()
	: Elysium::Core::Math::Numerics::Vector4Template<double>()
{
}
Elysium::Core::Math::Numerics::Vector4Double::Vector4Double(double Value)
	: Elysium::Core::Math::Numerics::Vector4Template<double>(Value)
{
}
Elysium::Core::Math::Numerics::Vector4Double::Vector4Double(double ValueX, double ValueY, double ValueZ, double ValueW)
	: Elysium::Core::Math::Numerics::Vector4Template<double>(ValueX, ValueY, ValueZ, ValueW)
{
}
Elysium::Core::Math::Numerics::Vector4Double::~Vector4Double()
{
}

Elysium::Core::Math::Numerics::Vector4Double Elysium::Core::Math::Numerics::Vector4Double::One()
{
	return Vector4Double(1.0);
}
Elysium::Core::Math::Numerics::Vector4Double Elysium::Core::Math::Numerics::Vector4Double::UnitX()
{
	return Vector4Double(1.0, 0.0, 0.0, 0.0);
}
Elysium::Core::Math::Numerics::Vector4Double Elysium::Core::Math::Numerics::Vector4Double::UnitY()
{
	return Vector4Double(0.0, 1.0, 0.0, 0.0);
}
Elysium::Core::Math::Numerics::Vector4Double Elysium::Core::Math::Numerics::Vector4Double::UnitZ()
{
	return Vector4Double(0.0, 0.0, 1.0, 0.0);
}
Elysium::Core::Math::Numerics::Vector4Double Elysium::Core::Math::Numerics::Vector4Double::UnitW()
{
	return Vector4Double(0.0, 0.0, 0.0, 1.0);
}
Elysium::Core::Math::Numerics::Vector4Double Elysium::Core::Math::Numerics::Vector4Double::Zero()
{
	return Vector4Double(0.0);
}

Elysium::Core::Math::Numerics::Vector4Single Elysium::Core::Math::Numerics::Vector4Double::ToVector4Single()
{
	return Vector4Single((float)X, (float)Y, (float)Z, (float)W);
}
