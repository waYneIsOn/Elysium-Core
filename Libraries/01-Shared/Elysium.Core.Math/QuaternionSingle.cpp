#include "QuaternionSingle.hpp"

Elysium::Core::Math::Numerics::QuaternionSingle::QuaternionSingle(float ValueX, float ValueY, float ValueZ, float ValueW)
	: Elysium::Core::Math::Numerics::QuaternionTemplate<float>(ValueX, ValueY, ValueZ, ValueW)
{
}
Elysium::Core::Math::Numerics::QuaternionSingle::~QuaternionSingle()
{
}

Elysium::Core::Math::Numerics::QuaternionSingle Elysium::Core::Math::Numerics::QuaternionSingle::Identity()
{
	return QuaternionSingle(0.0f, 0.0f, 0.0f, 1.0f);
}
