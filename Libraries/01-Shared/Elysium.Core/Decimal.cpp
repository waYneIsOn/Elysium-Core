#include "Decimal.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../Elysium.Core.Template/Move.hpp"
#endif

Elysium::Core::Decimal::Decimal()
	: _HighPart(0), _LowPart(0)
{ }

Elysium::Core::Decimal::Decimal(const float Value)
	: _HighPart(static_cast<Elysium::Core::int64_t>(Value)), _LowPart(static_cast<Elysium::Core::int64_t>(static_cast<double>(Value) * 100000) % 100000)
{ }

Elysium::Core::Decimal::Decimal(const double Value)
	: _HighPart(static_cast<Elysium::Core::int64_t>(Value)), _LowPart(static_cast<Elysium::Core::int64_t>(Value * 100000) % 100000)
{ }

Elysium::Core::Decimal::Decimal(const long double Value)
	: _HighPart(static_cast<Elysium::Core::int64_t>(Value)), _LowPart(static_cast<Elysium::Core::int64_t>(Value * 100000) % 100000)
{ }

Elysium::Core::Decimal::Decimal(const Elysium::Core::int64_t HighPart, const Elysium::Core::uint64_t LowPart)
	: _HighPart(HighPart), _LowPart(LowPart)
{ }

Elysium::Core::Decimal::Decimal(const Decimal & Source)
	: _HighPart(Source._HighPart), _LowPart(Source._LowPart)
{ }

Elysium::Core::Decimal::Decimal(Decimal && Right) noexcept
	: _HighPart(0), _LowPart(0)
{
	*this = Elysium::Core::Template::Functional::Move(Right);
}

Elysium::Core::Decimal::~Decimal()
{ }

Elysium::Core::Decimal & Elysium::Core::Decimal::operator=(const Decimal & Source)
{
	if (this != &Source)
	{
		_HighPart = Source._HighPart;
		_LowPart = Source._LowPart;
	}
	return *this;
}

Elysium::Core::Decimal & Elysium::Core::Decimal::operator=(Decimal && Right) noexcept
{
	if (this != &Right)
	{
		_HighPart = Elysium::Core::Template::Functional::Move(Right._HighPart);
		_LowPart = Elysium::Core::Template::Functional::Move(Right._LowPart);

		Right._HighPart = 0;
		Right._LowPart = 0;
}
	return *this;
}

const bool Elysium::Core::Decimal::operator==(const Elysium::Core::Decimal& Other) const
{
	return _HighPart == Other._HighPart && _LowPart == Other._LowPart;
}

const bool Elysium::Core::Decimal::operator!=(const Elysium::Core::Decimal& Other) const
{
	return _HighPart != Other._HighPart || _LowPart != Other._LowPart;
}

const bool Elysium::Core::Decimal::operator<(const Elysium::Core::Decimal& Other) const
{
	return _HighPart <= Other._HighPart && _LowPart < Other._LowPart;
}

const bool Elysium::Core::Decimal::operator>(const Elysium::Core::Decimal& Other) const
{
	return _HighPart >= Other._HighPart && _LowPart > Other._LowPart;
}

const bool Elysium::Core::Decimal::operator<=(const Elysium::Core::Decimal& Other) const
{
	return _HighPart <= Other._HighPart && _LowPart <= Other._LowPart;
}

const bool Elysium::Core::Decimal::operator>=(const Elysium::Core::Decimal& Other) const
{
	return _HighPart >= Other._HighPart && _LowPart >= Other._LowPart;
}

const bool Elysium::Core::Decimal::operator==(const Elysium::Core::int32_t& Other) const
{
	return _LowPart == 0 && _HighPart == Other;
}

const bool Elysium::Core::Decimal::operator!=(const Elysium::Core::int32_t& Other) const
{
	return _LowPart != 0 || _HighPart != Other;
}

const bool Elysium::Core::Decimal::operator<(const Elysium::Core::int32_t& Other) const
{
	return _HighPart < Other;
}

const bool Elysium::Core::Decimal::operator>(const Elysium::Core::int32_t& Other) const
{
	return _HighPart > Other || (_HighPart == Other && _LowPart > 0);
}

const bool Elysium::Core::Decimal::operator<=(const Elysium::Core::int32_t& Other) const
{
	return _HighPart < Other || (_HighPart == Other && _LowPart == 0);
}

const bool Elysium::Core::Decimal::operator>=(const Elysium::Core::int32_t& Other) const
{
	return _HighPart > Other || (_HighPart == Other && _LowPart > 0);
}

const Elysium::Core::int64_t& Elysium::Core::Decimal::GetHighPart() const
{
	return _HighPart;
}

const Elysium::Core::uint64_t& Elysium::Core::Decimal::GetLowPart() const
{
	return _LowPart;
}
