#include "Vector2Single.hpp"

Elysium::Core::Math::Numerics::Vector2Single::Vector2Single()
	: Elysium::Core::Math::Numerics::Vector2Template<float>()
{
}
Elysium::Core::Math::Numerics::Vector2Single::Vector2Single(float Value)
	: Elysium::Core::Math::Numerics::Vector2Template<float>(Value)
{
}
Elysium::Core::Math::Numerics::Vector2Single::Vector2Single(float ValueX, float ValueY)
	: Elysium::Core::Math::Numerics::Vector2Template<float>(ValueX, ValueY)
{
}
Elysium::Core::Math::Numerics::Vector2Single::~Vector2Single()
{
}

Elysium::Core::Math::Numerics::Vector2Single Elysium::Core::Math::Numerics::Vector2Single::One()
{
	return Vector2Single(1.0f);
}
Elysium::Core::Math::Numerics::Vector2Single Elysium::Core::Math::Numerics::Vector2Single::UnitX()
{
	return Vector2Single(1.0f, 0.0f);
}
Elysium::Core::Math::Numerics::Vector2Single Elysium::Core::Math::Numerics::Vector2Single::UnitY()
{
	return Vector2Single(0.0f, 1.0f);
}
Elysium::Core::Math::Numerics::Vector2Single Elysium::Core::Math::Numerics::Vector2Single::Zero()
{
	return Vector2Single(0.0f);
}
