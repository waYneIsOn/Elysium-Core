#include "Vector3Single.hpp"

Elysium::Core::Math::Numerics::Vector3Single::Vector3Single()
	: Elysium::Core::Math::Numerics::Vector3Template<float>()
{
}
Elysium::Core::Math::Numerics::Vector3Single::Vector3Single(float Value)
	: Elysium::Core::Math::Numerics::Vector3Template<float>(Value)
{
}
Elysium::Core::Math::Numerics::Vector3Single::Vector3Single(float ValueX, float ValueY, float ValueZ)
	: Elysium::Core::Math::Numerics::Vector3Template<float>(ValueX, ValueY, ValueZ)
{
}
Elysium::Core::Math::Numerics::Vector3Single::~Vector3Single()
{
}

Elysium::Core::Math::Numerics::Vector3Single Elysium::Core::Math::Numerics::Vector3Single::Backward()
{
	return Vector3Single(0.0f, 0.0f, 1.0f);
}
Elysium::Core::Math::Numerics::Vector3Single Elysium::Core::Math::Numerics::Vector3Single::Down()
{
	return Vector3Single(0.0f, -1.0f, 0.0f);
}
Elysium::Core::Math::Numerics::Vector3Single Elysium::Core::Math::Numerics::Vector3Single::Forward()
{
	return Vector3Single(0.0f, 0.0f, -1.0f);
}
Elysium::Core::Math::Numerics::Vector3Single Elysium::Core::Math::Numerics::Vector3Single::Left()
{
	return Vector3Single(-1.0f, 0.0f, 0.0f);
}
Elysium::Core::Math::Numerics::Vector3Single Elysium::Core::Math::Numerics::Vector3Single::One()
{
	return Vector3Single(1.0f);
}
Elysium::Core::Math::Numerics::Vector3Single Elysium::Core::Math::Numerics::Vector3Single::Right()
{
	return Vector3Single(1.0f, 0.0f, 0.0f);
}
Elysium::Core::Math::Numerics::Vector3Single Elysium::Core::Math::Numerics::Vector3Single::UnitX()
{
	return Vector3Single(1.0f, 0.0f, 0.0f);
}
Elysium::Core::Math::Numerics::Vector3Single Elysium::Core::Math::Numerics::Vector3Single::UnitY()
{
	return Vector3Single(0.0f, 1.0f, 0.0f);
}
Elysium::Core::Math::Numerics::Vector3Single Elysium::Core::Math::Numerics::Vector3Single::UnitZ()
{
	return Vector3Single(0.0f, 0.0f, 1.0f);
}
Elysium::Core::Math::Numerics::Vector3Single Elysium::Core::Math::Numerics::Vector3Single::Up()
{
	return Vector3Single(0.0f, 1.0f, 0.0f);
}
Elysium::Core::Math::Numerics::Vector3Single Elysium::Core::Math::Numerics::Vector3Single::Zero()
{
	return Vector3Single(0.0f);
}
