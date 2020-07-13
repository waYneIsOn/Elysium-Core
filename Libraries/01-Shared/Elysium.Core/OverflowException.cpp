#include "OverflowException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::OverflowException::OverflowException()
	: Elysium::Core::ArithmeticException(u"OverflowException")
{ }
Elysium::Core::OverflowException::OverflowException(const char16_t * Message)
	: Elysium::Core::ArithmeticException(Message)
{ }
Elysium::Core::OverflowException::OverflowException(String && Message)
	: Elysium::Core::ArithmeticException(std::move(Message))
{ }
Elysium::Core::OverflowException::~OverflowException()
{ }
