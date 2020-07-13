#include "ArithmeticException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::ArithmeticException::ArithmeticException()
	: Elysium::Core::SystemException(u"ArgumentNullException")
{ }
Elysium::Core::ArithmeticException::ArithmeticException(const char16_t * Message)
	: Elysium::Core::SystemException(Message)
{ }
Elysium::Core::ArithmeticException::ArithmeticException(String && Message)
	: Elysium::Core::SystemException(std::move(Message))
{ }
Elysium::Core::ArithmeticException::~ArithmeticException()
{ }
