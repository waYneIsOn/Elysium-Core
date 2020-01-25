#include "InterlockedInt64.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef ELYSIUM_CORE_THREADING_SYSTEM
#include "System.hpp"
#endif

Elysium::Core::Threading::InterlockedInt64::InterlockedInt64()
	: _Value(0)
{ }
Elysium::Core::Threading::InterlockedInt64::InterlockedInt64(const int64_t InitialValue)
	: _Value(InitialValue)
{ }
Elysium::Core::Threading::InterlockedInt64::InterlockedInt64(const InterlockedInt64 & Source)
	: _Value(Source._Value)
{ }
Elysium::Core::Threading::InterlockedInt64::InterlockedInt64(InterlockedInt64 && Right) noexcept
	: _Value(0)
{
	*this = std::move(Right);
}
Elysium::Core::Threading::InterlockedInt64::~InterlockedInt64()
{ }

Elysium::Core::Threading::InterlockedInt64 & Elysium::Core::Threading::InterlockedInt64::operator=(const InterlockedInt64 & Source)
{
	if (this != &Source)
	{
		_Value = int32_t(Source._Value);
	}
	return *this;
}
Elysium::Core::Threading::InterlockedInt64 & Elysium::Core::Threading::InterlockedInt64::operator=(InterlockedInt64 && Right) noexcept
{
	if (this != &Right)
	{
		_Value = std::move(Right._Value);

		Right._Value = 0;
	}
	return *this;
}

Elysium::Core::int64_t Elysium::Core::Threading::InterlockedInt64::operator++()
{
	return ELYSIUM_INTERLOCKED_INCREMENT64(reinterpret_cast<__int64*>(&_Value));
}
Elysium::Core::int64_t Elysium::Core::Threading::InterlockedInt64::operator--()
{
	return ELYSIUM_INTERLOCKED_DECREMENT64(reinterpret_cast<__int64*>(&_Value));
}

Elysium::Core::int64_t Elysium::Core::Threading::InterlockedInt64::operator+=(const int64_t Value)
{
	return ELYSIUM_INTERLOCKED_ADD64(reinterpret_cast<__int64*>(&_Value), Value);
}
Elysium::Core::int64_t Elysium::Core::Threading::InterlockedInt64::operator-=(const int64_t Value)
{
	return ELYSIUM_INTERLOCKED_ADD64(reinterpret_cast<__int64*>(&_Value), Value * -1);
}
