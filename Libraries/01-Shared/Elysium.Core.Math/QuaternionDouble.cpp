#include "QuaternionDouble.hpp"

Elysium::Core::Math::Numerics::QuaternionDouble::QuaternionDouble(double ValueX, double ValueY, double ValueZ, double ValueW)
	: Elysium::Core::Math::Numerics::QuaternionTemplate<double>(ValueX, ValueY, ValueZ, ValueW)
{
}
Elysium::Core::Math::Numerics::QuaternionDouble::~QuaternionDouble()
{
}

Elysium::Core::Math::Numerics::QuaternionDouble Elysium::Core::Math::Numerics::QuaternionDouble::Identity()
{
	return QuaternionDouble(0.0, 0.0, 0.0, 1.0);
}
