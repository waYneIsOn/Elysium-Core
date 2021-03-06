#include "DivideByZeroException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::DivideByZeroException::DivideByZeroException()
	: Elysium::Core::ArithmeticException(u8"DivideByZeroException")
{ }
Elysium::Core::DivideByZeroException::DivideByZeroException(const char8_t* Message)
	: Elysium::Core::ArithmeticException(Message)
{ }
Elysium::Core::DivideByZeroException::DivideByZeroException(Elysium::Core::String&& Message)
	: Elysium::Core::ArithmeticException(std::move(Message))
{ }
Elysium::Core::DivideByZeroException::~DivideByZeroException()
{ }
