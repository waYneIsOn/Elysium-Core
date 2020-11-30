#include "OverflowException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::OverflowException::OverflowException()
	: Elysium::Core::ArithmeticException(u8"OverflowException")
{ }
Elysium::Core::OverflowException::OverflowException(const char8_t* Message)
	: Elysium::Core::ArithmeticException(Message)
{ }
Elysium::Core::OverflowException::OverflowException(Elysium::Core::String&& Message)
	: Elysium::Core::ArithmeticException(std::move(Message))
{ }
Elysium::Core::OverflowException::~OverflowException()
{ }
