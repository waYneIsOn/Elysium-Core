#include "Vector2Double.hpp"

Elysium::Core::Math::Numerics::Vector2Double::Vector2Double()
{
}
Elysium::Core::Math::Numerics::Vector2Double::Vector2Double(double Value)
{
}
Elysium::Core::Math::Numerics::Vector2Double::Vector2Double(double ValueX, double ValueY)
{
}
Elysium::Core::Math::Numerics::Vector2Double::~Vector2Double()
{
}

Elysium::Core::Math::Numerics::Vector2Double Elysium::Core::Math::Numerics::Vector2Double::One()
{
	return Vector2Double(1.0);
}
Elysium::Core::Math::Numerics::Vector2Double Elysium::Core::Math::Numerics::Vector2Double::UnitX()
{
	return Vector2Double(1.0, 0.0);
}
Elysium::Core::Math::Numerics::Vector2Double Elysium::Core::Math::Numerics::Vector2Double::UnitY()
{
	return Vector2Double(0.0, 1.0);
}
Elysium::Core::Math::Numerics::Vector2Double Elysium::Core::Math::Numerics::Vector2Double::Zero()
{
	return Vector2Double(0.0);
}

Elysium::Core::Math::Numerics::Vector2Single Elysium::Core::Math::Numerics::Vector2Double::ToVector2Single()
{
	return Vector2Single((float)X, (float)Y);
}
