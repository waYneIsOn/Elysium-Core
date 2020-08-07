#include "ArgumentOutOfRangeException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::ArgumentOutOfRangeException::ArgumentOutOfRangeException()
	: Elysium::Core::ArgumentException(u8"ArgumentNullException")
{ }
Elysium::Core::ArgumentOutOfRangeException::ArgumentOutOfRangeException(const char * Message)
	: Elysium::Core::ArgumentException(Message)
{ }
Elysium::Core::ArgumentOutOfRangeException::ArgumentOutOfRangeException(String && Message)
	: Elysium::Core::ArgumentException(std::move(Message))
{ }
Elysium::Core::ArgumentOutOfRangeException::~ArgumentOutOfRangeException()
{ }
