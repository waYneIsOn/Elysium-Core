#include "Vector3Double.hpp"

Elysium::Core::Math::Numerics::Vector3Double::Vector3Double()
{
}
Elysium::Core::Math::Numerics::Vector3Double::Vector3Double(double Value)
{
}
Elysium::Core::Math::Numerics::Vector3Double::Vector3Double(double ValueX, double ValueY, double ValueZ)
{
}
Elysium::Core::Math::Numerics::Vector3Double::~Vector3Double()
{
}

Elysium::Core::Math::Numerics::Vector3Double Elysium::Core::Math::Numerics::Vector3Double::Backward()
{
	return Vector3Double(0.0, 0.0, 1.0);
}
Elysium::Core::Math::Numerics::Vector3Double Elysium::Core::Math::Numerics::Vector3Double::Down()
{
	return Vector3Double(0.0, -1.0, 0.0);
}
Elysium::Core::Math::Numerics::Vector3Double Elysium::Core::Math::Numerics::Vector3Double::Forward()
{
	return Vector3Double(0.0, 0.0, -1.0);
}
Elysium::Core::Math::Numerics::Vector3Double Elysium::Core::Math::Numerics::Vector3Double::Left()
{
	return Vector3Double(-1.0, 0.0, 0.0);
}
Elysium::Core::Math::Numerics::Vector3Double Elysium::Core::Math::Numerics::Vector3Double::One()
{
	return Vector3Double(1.0);
}
Elysium::Core::Math::Numerics::Vector3Double Elysium::Core::Math::Numerics::Vector3Double::Right()
{
	return Vector3Double(1.0, 0.0, 0.0);
}
Elysium::Core::Math::Numerics::Vector3Double Elysium::Core::Math::Numerics::Vector3Double::UnitX()
{
	return Vector3Double(1.0, 0.0, 0.0);
}
Elysium::Core::Math::Numerics::Vector3Double Elysium::Core::Math::Numerics::Vector3Double::UnitY()
{
	return Vector3Double(0.0, 1.0, 0.0);
}
Elysium::Core::Math::Numerics::Vector3Double Elysium::Core::Math::Numerics::Vector3Double::UnitZ()
{
	return Vector3Double(0.0, 0.0, 1.0);
}
Elysium::Core::Math::Numerics::Vector3Double Elysium::Core::Math::Numerics::Vector3Double::Up()
{
	return Vector3Double(0.0, 1.0, 0.0);
}
Elysium::Core::Math::Numerics::Vector3Double Elysium::Core::Math::Numerics::Vector3Double::Zero()
{
	return Vector3Double(0.0);
}

Elysium::Core::Math::Numerics::Vector3Single Elysium::Core::Math::Numerics::Vector3Double::ToVector3Single()
{
	return Vector3Single((float)X, (float)Y, (float)Z);
}
