#include "InterlockedInt32.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

Elysium::Core::Threading::InterlockedInt32::InterlockedInt32()
	: _Value(0)
{ }
Elysium::Core::Threading::InterlockedInt32::InterlockedInt32(const int32_t InitialValue)
	: _Value(InitialValue)
{ }
Elysium::Core::Threading::InterlockedInt32::InterlockedInt32(const InterlockedInt32 & Source)
	: _Value(Source._Value)
{ }
Elysium::Core::Threading::InterlockedInt32::InterlockedInt32(InterlockedInt32 && Right) noexcept
	: _Value(0)
{
	*this = std::move(Right);
}
Elysium::Core::Threading::InterlockedInt32::~InterlockedInt32()
{ }

Elysium::Core::Threading::InterlockedInt32 & Elysium::Core::Threading::InterlockedInt32::operator=(const InterlockedInt32 & Source)
{
	if (this != &Source)
	{
		_Value = int32_t(Source._Value);
	}
	return *this;
}
Elysium::Core::Threading::InterlockedInt32 & Elysium::Core::Threading::InterlockedInt32::operator=(InterlockedInt32 && Right) noexcept
{
	if (this != &Right)
	{
		_Value = std::move(Right._Value);

		Right._Value = 0;
	}
	return *this;
}

Elysium::Core::int32_t Elysium::Core::Threading::InterlockedInt32::operator++()
{
	return ELYSIUM_INTERLOCKED_INCREMENT(reinterpret_cast<long*>(&_Value));
}
Elysium::Core::int32_t Elysium::Core::Threading::InterlockedInt32::operator--()
{
	return ELYSIUM_INTERLOCKED_DECREMENT(reinterpret_cast<long*>(&_Value));
}

Elysium::Core::int32_t Elysium::Core::Threading::InterlockedInt32::operator+=(const int32_t Value)
{
	return ELYSIUM_INTERLOCKED_ADD(reinterpret_cast<long*>(&_Value), Value);
}
Elysium::Core::int32_t Elysium::Core::Threading::InterlockedInt32::operator-=(const int32_t Value)
{
	return ELYSIUM_INTERLOCKED_ADD(reinterpret_cast<long*>(&_Value), Value * -1);
}
