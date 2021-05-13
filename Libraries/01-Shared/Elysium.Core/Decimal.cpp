#include "Decimal.hpp"

#ifndef __midl
#include <cstring>
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

constexpr Elysium::Core::Decimal::Decimal()
	: _HighPart(0), _LowPart(0)
{ }
constexpr Elysium::Core::Decimal::Decimal(const float Value)
	: _HighPart(static_cast<Elysium::Core::int64_t>(Value)), _LowPart(static_cast<Elysium::Core::int64_t>(static_cast<double>(Value) * 100000) % 100000)
{ }
constexpr Elysium::Core::Decimal::Decimal(const double Value)
	: _HighPart(static_cast<Elysium::Core::int64_t>(Value)), _LowPart(static_cast<Elysium::Core::int64_t>(Value * 100000) % 100000)
{ }
constexpr Elysium::Core::Decimal::Decimal(const long double Value)
	: _HighPart(static_cast<Elysium::Core::int64_t>(Value)), _LowPart(static_cast<Elysium::Core::int64_t>(Value * 100000) % 100000)
{ }
constexpr Elysium::Core::Decimal::Decimal(const Elysium::Core::int64_t HighPart, const Elysium::Core::uint64_t LowPart)
	: _HighPart(HighPart), _LowPart(LowPart)
{ }
constexpr Elysium::Core::Decimal::Decimal(const Decimal & Source)
	: _HighPart(Source._HighPart), _LowPart(Source._LowPart)
{ }
constexpr Elysium::Core::Decimal::Decimal(Decimal && Right) noexcept
	: _HighPart(0), _LowPart(0)
{
	*this = std::move(Right);
}
constexpr Elysium::Core::Decimal::~Decimal()
{ }

constexpr Elysium::Core::Decimal & Elysium::Core::Decimal::operator=(const Decimal & Source)
{
	if (this != &Source)
	{
		_HighPart = Source._HighPart;
		_LowPart = Source._LowPart;
	}
	return *this;
}

constexpr Elysium::Core::Decimal & Elysium::Core::Decimal::operator=(Decimal && Right) noexcept
{
	if (this != &Right)
	{
		_HighPart = std::move(Right._HighPart);
		_LowPart = std::move(Right._LowPart);

		Right._HighPart = 0;
		Right._LowPart = 0;
}
	return *this;
}

constexpr const bool Elysium::Core::Decimal::operator==(const Elysium::Core::Decimal& Other) const
{
	return _HighPart == Other._HighPart && _LowPart == Other._LowPart;
}

constexpr const bool Elysium::Core::Decimal::operator!=(const Elysium::Core::Decimal& Other) const
{
	return _HighPart != Other._HighPart || _LowPart != Other._LowPart;
}

constexpr const bool Elysium::Core::Decimal::operator<(const Elysium::Core::Decimal& Other) const
{
	return _HighPart <= Other._HighPart && _LowPart < Other._LowPart;
}

constexpr const bool Elysium::Core::Decimal::operator>(const Elysium::Core::Decimal& Other) const
{
	return _HighPart >= Other._HighPart && _LowPart > Other._LowPart;
}

constexpr const bool Elysium::Core::Decimal::operator<=(const Elysium::Core::Decimal& Other) const
{
	return _HighPart <= Other._HighPart && _LowPart <= Other._LowPart;
}

constexpr const bool Elysium::Core::Decimal::operator>=(const Elysium::Core::Decimal& Other) const
{
	return _HighPart >= Other._HighPart && _LowPart >= Other._LowPart;
}

constexpr const Elysium::Core::int64_t& Elysium::Core::Decimal::GetHighPart() const
{
	return _HighPart;
}

constexpr const Elysium::Core::uint64_t& Elysium::Core::Decimal::GetLowPart() const
{
	return _LowPart;
}
