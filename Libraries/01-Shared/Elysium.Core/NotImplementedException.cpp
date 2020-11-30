#include "NotImplementedException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Core::NotImplementedException::NotImplementedException()
	: Elysium::Core::Exception(u8"NotImplementedException")
{ }
Elysium::Core::NotImplementedException::NotImplementedException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Core::NotImplementedException::NotImplementedException(Elysium::Core::String&& Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Core::NotImplementedException::~NotImplementedException()
{ }
