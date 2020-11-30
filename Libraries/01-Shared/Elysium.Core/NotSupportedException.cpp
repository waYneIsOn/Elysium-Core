#include "NotSupportedException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::NotSupportedException::NotSupportedException()
	: Elysium::Core::Exception(u8"NotSupportedException")
{ }
Elysium::Core::NotSupportedException::NotSupportedException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::NotSupportedException::NotSupportedException(String && Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::NotSupportedException::~NotSupportedException()
{ }
