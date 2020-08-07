#include "ArgumentNullException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::ArgumentNullException::ArgumentNullException()
	: Elysium::Core::ArgumentException(u8"ArgumentNullException")
{ }
Elysium::Core::ArgumentNullException::ArgumentNullException(const char * Message)
	: Elysium::Core::ArgumentException(Message)
{ }
Elysium::Core::ArgumentNullException::ArgumentNullException(String && Message)
	: Elysium::Core::ArgumentException(std::move(Message))
{ }
Elysium::Core::ArgumentNullException::~ArgumentNullException()
{ }
