#include "ArgumentOutOfRangeException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::ArgumentOutOfRangeException::ArgumentOutOfRangeException()
	: Elysium::Core::Exception(u"ArgumentNullException")
{ }
Elysium::Core::ArgumentOutOfRangeException::ArgumentOutOfRangeException(const char16_t * Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::ArgumentOutOfRangeException::ArgumentOutOfRangeException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::ArgumentOutOfRangeException::~ArgumentOutOfRangeException()
{ }
