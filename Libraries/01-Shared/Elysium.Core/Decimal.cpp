#include "Decimal.hpp"

#ifndef __midl
#include <cstring>
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::Decimal::Decimal()
	: _Data()
{ }
Elysium::Core::Decimal::Decimal(const float & Value)
	: _Data()
{
	int64_t HighPart = (int64_t)Value;
	int64_t LowPart = int64_t(static_cast<double>(Value) * 100000) % 100000;

	memcpy(&_Data[0], &HighPart, sizeof(int64_t));
	memcpy(&_Data[8], &LowPart, sizeof(int64_t));
}
Elysium::Core::Decimal::Decimal(const double & Value)
	: _Data()
{
	int64_t HighPart = (int64_t)Value;
	int64_t LowPart = int64_t(Value * 100000) % 100000;

	memcpy(&_Data[0], &HighPart, sizeof(int64_t));
	memcpy(&_Data[8], &LowPart, sizeof(int64_t));
}
Elysium::Core::Decimal::Decimal(const int64_t & HighPart, const int64_t & LowPart)
	: _Data()
{
	memcpy(&_Data[0], &HighPart, sizeof(int64_t));
	memcpy(&_Data[8], &LowPart, sizeof(int64_t));
}
Elysium::Core::Decimal::Decimal(const Decimal & Source)
	: _Data()
{
	memcpy(&_Data[0], &Source._Data[0], sizeof(byte) * 16);
}
Elysium::Core::Decimal::Decimal(Decimal && Right) noexcept
	: _Data()
{
	*this = std::move(Right);
}
Elysium::Core::Decimal::~Decimal()
{ }

Elysium::Core::Decimal & Elysium::Core::Decimal::operator=(const Decimal & Source)
{
	if (this != &Source)
	{
		memcpy(&_Data[0], &Source._Data[0], sizeof(byte) * 16);
	}
	return *this;
}
Elysium::Core::Decimal & Elysium::Core::Decimal::operator=(Decimal && Right) noexcept
{
	if (this != &Right)
	{
		memmove(_Data, Right._Data, sizeof(byte) * 16);
		memset(Right._Data, 0, sizeof(byte) * 16);
}
	return *this;
}

const Elysium::Core::int64_t Elysium::Core::Decimal::GetHighPart() const
{
#ifdef BIGENDIAN
	return *(int64_t*)&_Data[8];
#else
	return *(int64_t*)&_Data[0];
#endif
}
const Elysium::Core::int64_t Elysium::Core::Decimal::GetLowPart() const
{
#ifdef BIGENDIAN
	return *(int64_t*)&_Data[0];
#else
	return *(int64_t*)&_Data[8];
#endif
}
