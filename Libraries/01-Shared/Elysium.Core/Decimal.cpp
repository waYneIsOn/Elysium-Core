#include "Decimal.hpp"

#ifndef __midl
#include <cstring>
#endif

Elysium::Core::Decimal::Decimal()
{
}
Elysium::Core::Decimal::Decimal(const float & Value)
{
	int64_t HighPart = (int64_t)Value;
	int64_t LowPart = int64_t(Value * 100000) % 100000;

	memcpy(&_Data[0], &HighPart, sizeof(int64_t));
	memcpy(&_Data[8], &LowPart, sizeof(int64_t));
}
Elysium::Core::Decimal::Decimal(const double & Value)
{
	int64_t HighPart = (int64_t)Value;
	int64_t LowPart = int64_t(Value * 100000) % 100000;

	memcpy(&_Data[0], &HighPart, sizeof(int64_t));
	memcpy(&_Data[8], &LowPart, sizeof(int64_t));
}
Elysium::Core::Decimal::Decimal(const int64_t & HighPart, const int64_t & LowPart)
{
	memcpy(&_Data[0], &HighPart, sizeof(int64_t));
	memcpy(&_Data[8], &LowPart, sizeof(int64_t));
}
Elysium::Core::Decimal::Decimal(const Decimal & Value)
{
	memcpy(&_Data[0], &Value, sizeof(Decimal));
}
Elysium::Core::Decimal::~Decimal()
{
}

const int64_t* Elysium::Core::Decimal::GetHighPart() const
{
#ifdef BIGENDIAN
	return (int64_t*)&_Data[8];
#else
	return (int64_t*)&_Data[0];
#endif
}
const int64_t * Elysium::Core::Decimal::GetLowPart() const
{
#ifdef BIGENDIAN
	return (int64_t*)&_Data[0];
#else
	return (int64_t*)&_Data[8];
#endif
}
