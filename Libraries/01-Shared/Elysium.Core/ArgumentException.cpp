#include "ArgumentException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::ArgumentException::ArgumentException()
	: Elysium::Core::SystemException(u8"ArgumentException")
{ }
Elysium::Core::ArgumentException::ArgumentException(const char8_t* Message)
	: Elysium::Core::SystemException(Message)
{ }
Elysium::Core::ArgumentException::ArgumentException(String && Message)
	: Elysium::Core::SystemException(std::move(Message))
{ }
Elysium::Core::ArgumentException::~ArgumentException()
{ }

