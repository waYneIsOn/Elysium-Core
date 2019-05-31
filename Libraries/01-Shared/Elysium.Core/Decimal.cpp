#include "Decimal.hpp"

#ifndef __midl
#include <cstring>
#endif

Elysium::Core::Decimal::Decimal()
{
}
Elysium::Core::Decimal::Decimal(const float & Value)
{
	__int64 HighPart = (__int64)Value;
	__int64 LowPart = __int64(Value * 100000) % 100000;

	memcpy(&_Data[0], &HighPart, sizeof(__int64));
	memcpy(&_Data[8], &LowPart, sizeof(__int64));
}
Elysium::Core::Decimal::Decimal(const double & Value)
{
	__int64 HighPart = (__int64)Value;
	__int64 LowPart = __int64(Value * 100000) % 100000;

	memcpy(&_Data[0], &HighPart, sizeof(__int64));
	memcpy(&_Data[8], &LowPart, sizeof(__int64));
}
Elysium::Core::Decimal::Decimal(const __int64 & HighPart, const __int64 & LowPart)
{
	memcpy(&_Data[0], &HighPart, sizeof(__int64));
	memcpy(&_Data[8], &LowPart, sizeof(__int64));
}
Elysium::Core::Decimal::Decimal(const Decimal & Value)
{
	memcpy(&_Data[0], &Value, sizeof(Decimal));
}
Elysium::Core::Decimal::~Decimal()
{
}

const __int64* Elysium::Core::Decimal::GetHighPart() const
{
#ifdef BIGENDIAN
	return (__int64*)&_Data[8];
#else
	return (__int64*)&_Data[0];
#endif
}
const __int64 * Elysium::Core::Decimal::GetLowPart() const
{
#ifdef BIGENDIAN
	return (__int64*)&_Data[0];
#else
	return (__int64*)&_Data[8];
#endif
}
